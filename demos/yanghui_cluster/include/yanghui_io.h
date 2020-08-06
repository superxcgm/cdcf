/*
 * Copyright (c) 2020 ThoughtWorks Inc.
 */

#ifndef DEMOS_YANGHUI_CLUSTER_INCLUDE_YANGHUI_IO_H_
#define DEMOS_YANGHUI_CLUSTER_INCLUDE_YANGHUI_IO_H_
#include <string>

#include <caf/openssl/all.hpp>

#include "../../../logger/include/logger.h"

class YanghuiIO {
  const bool use_ssl_;

 public:
  explicit YanghuiIO(bool if_use_ssl) : use_ssl_(if_use_ssl) {}

  template <class Handle>
  caf::expected<uint16_t> publish(const Handle& whom, uint16_t port,
                                  const char* in = nullptr,
                                  bool reuse = false) {
    return use_ssl_ ? caf::openssl::publish(whom, port, in, reuse)
                    : caf::io::publish(whom, port, in, reuse);
  }

  template <class ActorHandle = caf::actor>
  caf::expected<ActorHandle> remote_actor(caf::actor_system& system,
                                          std::string host, uint16_t port) {
    return use_ssl_ ? caf::openssl::remote_actor(system, host, port)
                    : caf::io::remote_actor(system, host, port);
  }

  bool IsUseSSL() const { return use_ssl_; }
};

#endif  // DEMOS_YANGHUI_CLUSTER_INCLUDE_YANGHUI_IO_H_
