/*
 * Copyright (c) 2019-2020 ThoughtWorks Inc.
 */

#ifndef ACTOR_SYSTEM_INCLUDE_CDCF_ACTOR_STATUS_MONITOR_H_
#define ACTOR_SYSTEM_INCLUDE_CDCF_ACTOR_STATUS_MONITOR_H_

#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <caf/all.hpp>
#include <caf/io/all.hpp>

#include "cdcf/actor_monitor.h"

namespace cdcf {
class ActorStatusMonitor {
 public:
  struct ActorInfo {
    std::uint64_t id;
    std::string name;
    std::string description;
  };
  virtual ~ActorStatusMonitor();

  explicit ActorStatusMonitor(caf::actor_system& actorSystem);
  void RegisterActor(caf::actor& actor, const std::string& name,
                     const std::string& description = "");
  std::vector<ActorInfo> GetActorStatus();

 private:
  caf::actor_system& actor_system_;
  caf::actor actor_monitor_;
  std::unordered_map<caf::actor_id, ActorInfo> actor_status_;
  std::mutex actor_status_lock_;
};
}  // namespace cdcf
#endif  // ACTOR_SYSTEM_INCLUDE_CDCF_ACTOR_STATUS_MONITOR_H_
