/*
 * Copyright (c) 2019-2020 ThoughtWorks Inc.
 */
#include "src/grpc.h"

#include <gmock/gmock.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

#include <chrono>
#include <future>
#include <memory>
#include <thread>

#include "src/membership.h"

using membership::Membership;
using node_keeper::GRPCImpl;
using node_keeper::GRPCServer;
using testing::Eq;

class GRPCTest : public ::testing::Test {
 protected:
  GRPCTest() {}

  void SetUp() override {
    service_ = std::make_unique<GRPCImpl>(membership);
    service_->SetHost("not_local");
    std::vector<grpc::Service*> services = {service_.get()};
    server_ = std::make_unique<GRPCServer>(server_address_, services);
    ResetStub();
  }

  void TearDown() override {
    service_->Close();
    server_.reset();
  }

  void ResetStub() {
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(
        server_address_, grpc::InsecureChannelCredentials());
    stub_ = NodeKeeper::NewStub(channel);
  }

  std::unique_ptr<NodeKeeper::Stub> stub_;
  /* FIXME: It would be better to find a unused port dynamically like
   * `grpc_pick_unused_port_or_die`. */
  const std::string server_address_{"127.0.0.1:30002"};
  Membership membership;
  std::unique_ptr<GRPCImpl> service_;
  std::unique_ptr<GRPCServer> server_;
  membership::Member node_a_ = {"node_a", "localhost", 8834};
  membership::Member node_b_ = {"node_b", "localhost", 8835};
};

TEST_F(GRPCTest, ShouldReturnNoneMemberByGetMembers) {
  ::GetMembersReply reply;
  grpc::ClientContext context;
  auto status = stub_->GetMembers(&context, {}, &reply);

  EXPECT_TRUE(status.ok());
  EXPECT_TRUE(reply.members().empty());
}

TEST_F(GRPCTest, ShouldReturnOneMemberByGetMembersAfterNodeUp) {
  service_->Notify({{node_keeper::MemberEvent::kMemberUp, node_a_}});

  ::GetMembersReply reply;
  grpc::ClientContext context;
  auto status = stub_->GetMembers(&context, {}, &reply);

  EXPECT_TRUE(status.ok());
  EXPECT_THAT(reply.members().size(), Eq(1));
}

TEST_F(GRPCTest, ShouldReturnNoneMemberByGetMembersAfterSameNodeUpAndDown) {
  service_->Notify({{node_keeper::MemberEvent::kMemberUp, node_a_}});
  service_->Notify({{node_keeper::MemberEvent::kMemberDown, node_a_}});

  ::GetMembersReply reply;
  grpc::ClientContext context;
  auto status = stub_->GetMembers(&context, {}, &reply);

  EXPECT_TRUE(status.ok());
  EXPECT_THAT(reply.members().size(), Eq(0));
}

TEST_F(GRPCTest, ShouldReturnOneMemberByGetMembersAfterDifferentNodeUpAndDown) {
  service_->Notify({{node_keeper::MemberEvent::kMemberUp, node_a_}});
  service_->Notify({{node_keeper::MemberEvent::kMemberDown, node_b_}});

  ::GetMembersReply reply;
  grpc::ClientContext context;
  auto status = stub_->GetMembers(&context, {}, &reply);

  EXPECT_TRUE(status.ok());
  EXPECT_THAT(reply.members().size(), Eq(1));
}

TEST_F(GRPCTest, ShouldReturnBySubscribeAfterDifferentNodeUpAndDown) {
  bool server_done = false;
  grpc::ClientContext context;
  std::unique_ptr<grpc::ClientReader<::Event>> reader(
      stub_->Subscribe(&context, {}));
  auto future = std::async([&]() {
    std::vector<::Event> events;
    for (::Event event; !server_done && reader->Read(&event);) {
      events.push_back(event);
    }
    return events;
  });

  for (size_t i = 0; i < 5 && service_->GetSubscribersCount() != 1;
       std::this_thread::sleep_for(std::chrono::milliseconds(100))) {
  }
  ASSERT_THAT(service_->GetSubscribersCount(), Eq(1));
  service_->Notify({{node_keeper::MemberEvent::kMemberUp, node_a_}});
  server_done = true;
  auto events = future.get();

  EXPECT_THAT(events.size(), Eq(1));
  EXPECT_THAT(events[0].type(), Eq(Event_Type_MEMBER_CHANGED));
  ::MemberEvent event;
  events[0].data().UnpackTo(&event);
  EXPECT_THAT(event.status(), Eq(::MemberEvent::UP));
  EXPECT_THAT(event.member().name(), Eq(node_a_.GetNodeName()));
  EXPECT_THAT(event.member().host(), Eq(node_a_.GetIpAddress()));
  EXPECT_THAT(event.member().port(), Eq(node_a_.GetPort()));
}

TEST_F(GRPCTest, ShouldGetHostNameWhenConfigWithHostName) {
  membership::Member node_c_ = {"node_c", "127.0.0.1", 8836, "localhost"};
  service_->Notify({{node_keeper::MemberEvent::kMemberUp, node_c_}});

  ::GetMembersReply reply;
  grpc::ClientContext context;
  auto status = stub_->GetMembers(&context, {}, &reply);

  EXPECT_TRUE(status.ok());
  EXPECT_THAT(reply.members().size(), Eq(1));
  EXPECT_THAT(reply.members(0).hostname(), "localhost");
  EXPECT_THAT(reply.members(0).host(), "127.0.0.1");
}
