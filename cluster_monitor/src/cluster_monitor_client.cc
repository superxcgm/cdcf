/*
 * Copyright (c) 2019-2020 ThoughtWorks Inc.
 */
#include <grpcpp/create_channel.h>

#include "../../config_manager/include/cdcf_config.h"
#include "./node_monitor.grpc.pb.h"

class ClientConfig : public CDCFConfig {
 public:
  std::string server_host = "localhost:50051";

  ClientConfig() {
    opt_group{custom_options_, "global"}.add(
        server_host, "host,H", "server ip and port, example: 10.13.2.2:50051");
  }
};

int main(int argc, char* argv[]) {
  ClientConfig input_parameter;
  CDCFConfig::RetValue parse_ret = input_parameter.parse_config(argc, argv);

  if (parse_ret != CDCFConfig::RetValue::kSuccess) {
    return 1;
  }

  auto channel = grpc::CreateChannel(input_parameter.server_host,
                                     grpc::InsecureChannelCredentials());
  ::NodeMonitor::Stub client(channel);

  grpc::ClientContext query_context;
  ::AllNodeStatus all_node_status;
  grpc::Status status =
      client.GetAllNodeStatus(&query_context, {}, &all_node_status);

  if (!status.ok()) {
    std::cout << "get cluster node ip:port=（" << input_parameter.server_host
              << ") status failed, error message:" << status.error_message()
              << std::endl;
    return 1;
  }

  std::cout << "Get cluster node status from:" << input_parameter.server_host
            << std::endl;
  std::cout << "Total node:" << all_node_status.node_status_size() << std::endl;

  for (auto& one_node_status : all_node_status.node_status()) {
    std::cout << "Cluster node ip:" << one_node_status.ip() << std::endl;

    if ("" == one_node_status.error_message()) {
      std::cout << "  Cpu use rate:" << one_node_status.cpu_use_rate() * 100
                << "%" << std::endl;
      std::cout << "  Memory use rate:" << one_node_status.mem_use_rate() * 100
                << "%" << std::endl;
      std::cout << "  Max memory:" << one_node_status.max_memory() << "kB"
                << std::endl;
      std::cout << "  Use memory:" << one_node_status.use_memory() << "kB"
                << std::endl;
    } else {
      std::cout << " error:" << one_node_status.error_message() << std::endl;
    }

    std::cout << std::endl;
  }
}