/*
 * Copyright (c) 2020 ThoughtWorks Inc.
 */

#ifndef CDCF_YANGHUI_CONFIG_H
#define CDCF_YANGHUI_CONFIG_H
#include <string>
#include <vector>

#include "caf/all.hpp"
#include "caf/io/all.hpp"
#include "cdcf_config.h"

struct NumberCompareData {
  std::vector<int> numbers;
  int index;
};

template <class Inspector>
typename Inspector::result_type inspect(Inspector& f, NumberCompareData& x) {
  return f(caf::meta::type_name("NumberCompareData"), x.numbers, x.index);
}

class config : public cdcf_config {
 public:
  uint16_t port = 0;
  std::string host = "localhost";
  std::string worker_group = "";
  std::string count_result_group = "";
  std::string compare_group = "";
  uint16_t worker_port = 0;

  config() {
    opt_group{custom_options_, "global"}
        .add(port, "port,p", "set port")
        .add(host, "host,H", "set node")
        .add(worker_group, "group,g", "set worker group name@host:port")
        .add(count_result_group, "result,r",
             "set count result group name@host:port")
        .add(compare_group, "compare, c",
             "set compare result group name@host:port")
        .add(worker_port, "instance, i", "set instance id");
    add_message_type<NumberCompareData>("NumberCompareData");
  }
};

#endif  // CDCF_YANGHUI_CONFIG_H
