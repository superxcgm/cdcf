/*
 * Copyright (c) 2019-2020 ThoughtWorks Inc.
 */

#ifndef NODE_KEEPER_SRC_MEMBERSHIP_MESSAGE_H_
#define NODE_KEEPER_SRC_MEMBERSHIP_MESSAGE_H_

#include <string>
#include <vector>

#include "protobuf/message.pb.h"
#include "src/membership.h"

namespace membership {

class Message {
 public:
  virtual google::protobuf::Message& BaseMessage() = 0;

  std::string SerializeToString();
  void DeserializeFromString(const std::string& data);
  void DeserializeFromArray(const void* data, int size);
};

class UpdateMessage : public Message {
 public:
  void InitAsUpMessage(const Member& member, unsigned int incarnation);
  void InitAsDownMessage(const Member& member, unsigned int incarnation);
  void InitAsSuspectMessage(const Member& member, unsigned int incarnation);
  bool IsUpMessage() const;
  bool IsDownMessage() const;
  bool IsSuspectMessage() const;
  Member GetMember() const;
  unsigned int GetIncarnation() const { return update_.incarnation(); }

  google::protobuf::Message& BaseMessage() override { return update_; }

 private:
  MemberUpdate update_;
  unsigned int incarnation_;
};

class FullStateMessage : public Message {
 public:
  void InitAsFullStateMessage(const std::vector<Member>& members);
  void InitAsReentryRejected();
  bool IsSuccess();
  std::vector<Member> GetMembers();

  google::protobuf::Message& BaseMessage() override { return state_; }

 private:
  MemberFullState state_;
};

};      // namespace membership
#endif  // NODE_KEEPER_SRC_MEMBERSHIP_MESSAGE_H_
