/*
 * Copyright (c) 2019-2020 ThoughtWorks Inc.
 */
#include "include/actor_system/cluster.h"

#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

#include <thread>

#include "src/node_keeper.grpc.pb.h"

namespace actor_system {
namespace cluster {

class ClusterImpl {
 public:
  ClusterImpl() {
    const std::string& host{"127.0.0.1"};
    const uint16_t port = 50051;
    auto address = host + ":" + std::to_string(port);
    auto channel =
        grpc::CreateChannel(address, grpc::InsecureChannelCredentials());
    stub_ = NodeKeeper::NewStub(channel);
    Fetch();
    thread_ = std::thread(&ClusterImpl::Routine, this);
  }

  ~ClusterImpl() {
    stop_ = true;
    if (thread_.joinable()) {
      thread_.join();
    }
  }

  std::vector<Member> GetMembers() {
    std::lock_guard lock(mutex_);
    return members_;
  }

 private:
  void Routine() {
    Fetch();
    grpc::ClientContext context;
    auto reader(stub_->Subscribe(&context, {}));
    for (::Event event; !stop_ && reader->Read(&event);) {
      Update(event);
    }
  }

  void Fetch() {
    ::GetMembersReply reply;
    grpc::ClientContext context;
    auto status = stub_->GetMembers(&context, {}, &reply);
    if (status.ok()) {
      std::vector<Member> members;
      members.reserve(reply.members().size());
      for (auto member : reply.members()) {
        auto port = static_cast<uint16_t>(member.port());
        members.push_back({member.host(), port, Member::Status::Up});
      }
      {
        std::lock_guard lock(mutex_);
        std::swap(members_, members);
      }
    }
  }

  void Update(::Event& event) {
    if (event.type() != Event_Type_MEMBER_CHANGED) {
      return;
    }
    ::MemberEvent member_event;
    event.data().UnpackTo(&member_event);
    auto port = static_cast<uint16_t>(member_event.member().port());
    Member member{member_event.member().host(), port};
    if (member_event.status() == ::MemberEvent::UP) {
      member.status = Member::Status::Up;
      std::lock_guard lock(mutex_);
      members_.push_back(member);
    } else if (member_event.status() == ::MemberEvent::DOWN) {
      member.status = Member::Status::Down;
      std::lock_guard lock(mutex_);
      auto it = std::remove(members_.begin(), members_.end(), member);
      members_.erase(it, members_.end());
    }
    Cluster::GetInstance()->Notify({member});
  }

  std::mutex mutex_;
  std::vector<Member> members_;
  std::unique_ptr<NodeKeeper::Stub> stub_;
  std::thread thread_;
  bool stop_{false};
};

std::mutex Cluster::instance_mutex_;
std::unique_ptr<Cluster> Cluster::instance_;

Cluster* Cluster::GetInstance() {
  if (instance_) {
    return &*instance_;
  }
  std::lock_guard lock(instance_mutex_);
  if (instance_) {
    return &*instance_;
  }
  instance_.reset(new Cluster());
  return &*instance_;
}

std::vector<Member> Cluster::GetMembers() { return impl_->GetMembers(); }

Cluster::Cluster() : impl_(std::make_unique<ClusterImpl>()) {}

Cluster::~Cluster() {}

}  // namespace cluster
};  // namespace actor_system
