/*
 * Copyright (c) 2020 ThoughtWorks Inc.
 */
#include <actor_system/cluster.h>

#include <climits>
#include <condition_variable>
#include <utility>

#include <caf/all.hpp>
#include <caf/io/all.hpp>

#include "../../actor_fault_tolerance/include/actor_guard.h"
#include "../../actor_fault_tolerance/include/actor_union.h"
#include "../../actor_monitor/include/actor_monitor.h"
#include "../../actor_system/include/actor_status_service_grpc_impl.h"
#include "./yanghui_config.h"

caf::actor StartWorker(caf::actor_system& system, const caf::node_id& nid,
                       const std::string& name, caf::message args,
                       std::chrono::seconds timeout, bool& active) {
  auto worker = system.middleman().remote_spawn<calculator>(
      nid, name, std::move(args), timeout);
  if (!worker) {
    std::cerr << "*** remote spawn failed: " << system.render(worker.error())
              << std::endl;

    active = false;
    return caf::actor{};
  }

  auto ret_actor = caf::actor_cast<caf::actor>(std::move(*worker));
  active = true;

  return ret_actor;
}

const uint16_t k_yanghui_work_port1 = 55001;

class WorkerPool : public actor_system::cluster::Observer {
 public:
  WorkerPool(caf::actor_system& system, std::string host, uint16_t worker_port)
      : system_(system), host_(std::move(host)), worker_port_(worker_port) {}

  int Init() {
    std::cout << "worker pool init" << std::endl;
    auto members = actor_system::cluster::Cluster::GetInstance()->GetMembers();
    actor_system::cluster::Cluster::GetInstance()->AddObserver(this);

    std::cout << "worker pool members size: " << members.size() << std::endl;
    for (const auto& member : members) {
      std::cout << "worker pool loop " << std::endl;
      if (member.hostname == host_ || member.host == host_) {
        continue;
      }
      auto ret = AddWorker(member.host);
      if (ret != 0) {
        return ret;
      }
    }
    std::cout << "worker pool init finish" << std::endl;
    return 0;
  }

  bool IsEmpty() { return workers_.empty(); }

  caf::strong_actor_ptr GetWorker() {
    std::cout << "get worker 1" << std::endl;
    if (workers_.empty()) {
      return caf::strong_actor_ptr();
    }
    if (worker_index_ == workers_.size() - 1) {
      worker_index_ = 0;
      std::cout << "get worker 3" << std::endl;
      return workers_[workers_.size() - 1];
    }
    std::cout << "get worker 2" << std::endl;
    return workers_[worker_index_++];
  }

  int AddWorker(const std::string& host) {
    std::cout << "add worker 1" << std::endl;
    auto node = system_.middleman().connect(host, worker_port_);
    if (!node) {
      std::cerr << "*** connect failed: " << to_string(node.error())
                << std::endl;
      return 1;
    }
    auto type = "calculator";              // type of the actor we wish to spawn
    auto args = caf::make_message();       // arguments to construct the actor
    auto tout = std::chrono::seconds(30);  // wait no longer than 30s
    std::cout << "add worker 2" << std::endl;
    auto worker1 =
        system_.middleman().remote_spawn<calculator>(*node, type, args, tout);
    if (!worker1) {
      std::cerr << "*** remote spawn failed: " << to_string(worker1.error())
                << std::endl;
      return 1;
    }
    auto worker2 =
        system_.middleman().remote_spawn<calculator>(*node, type, args, tout);
    if (!worker2) {
      std::cerr << "*** remote spawn failed: " << to_string(worker2.error())
                << std::endl;
      return 1;
    }
    auto worker3 =
        system_.middleman().remote_spawn<calculator>(*node, type, args, tout);
    if (!worker3) {
      std::cerr << "*** remote spawn failed: " << to_string(worker3.error())
                << std::endl;
      return 1;
    }

    std::cout << "add worker 1 with id: " << worker1->id() << std::endl;
    std::cout << "add worker 2 with id: " << worker2->id() << std::endl;
    std::cout << "add worker 3 with id: " << worker3->id() << std::endl;

    std::cout << "add worker 3" << std::endl;
    workers_.push_back(caf::actor_cast<caf::strong_actor_ptr>(*worker1));
    workers_.push_back(caf::actor_cast<caf::strong_actor_ptr>(*worker2));
    workers_.push_back(caf::actor_cast<caf::strong_actor_ptr>(*worker3));
    std::cout << "add worker 4" << std::endl;
    return 0;
  }

  void Update(const actor_system::cluster::Event& event) override {
    if (event.member.hostname != host_) {
      if (event.member.status == event.member.ActorSystemUp) {
        //         std::this_thread::sleep_for(std::chrono::seconds(2));
        AddWorker(event.member.host);
        PrintClusterMembers();
      } else if (event.member.status == event.member.Down) {
        std::cout << "detect worker node down, host:" << event.member.host
                  << " port:" << event.member.port << std::endl;
      } else if (event.member.status == event.member.ActorSystemDown) {
        std::cout << "detect worker actor system down, host:"
                  << event.member.host << " port:" << event.member.port
                  << std::endl;
      }
    }
  }

  void PrintClusterMembers() {
    auto members = actor_system::cluster::Cluster::GetInstance()->GetMembers();
    std::cout << "Current Cluster Members:" << std::endl;
    for (int i = 0; i < members.size(); ++i) {
      auto& member = members[i];
      std::cout << "Member " << i + 1 << ": ";
      std::cout << "name: " << member.name << ", hostname: " << member.hostname
                << ", host: " << member.host << ", port:" << member.port
                << std::endl;
    }
  }

 private:
  std::vector<caf::strong_actor_ptr> workers_;
  int worker_index_ = 0;
  std::string host_;
  caf::actor_system& system_;
  uint16_t worker_port_;
};

class CountCluster : public actor_system::cluster::Observer {
 public:
  CountCluster(std::string host, caf::actor_system& system, uint16_t port,
               uint16_t worker_port)
      : host_(std::move(host)),
        system_(system),
        port_(port),
        worker_port_(worker_port),
        counter_(system, caf::actor_pool::round_robin()) {
    supervisor_ = system.spawn<ActorMonitor>(
        [this](const caf::down_msg& down_msg,
               const std::string& actor_description) {
          downMsgHandle(down_msg, actor_description);
        });
    auto members = GetInstance()->GetMembers();
    InitWorkerNodes(members, host_, port_);
    GetInstance()->AddObserver(this);
    PrintClusterMembers();
  }
  ~CountCluster() { GetInstance()->RemoveObserver(this); }

  actor_system::cluster::Cluster* GetInstance() {
    return actor_system::cluster::Cluster::GetInstance();
  }

  void downMsgHandle(const caf::down_msg& down_msg,
                     const std::string& actor_description) {
    std::cout << std::endl;
    std::cout << "=============actor monitor call===============" << std::endl;
    std::cout << "down actor address:" << caf::to_string(down_msg.source)
              << std::endl;
    std::cout << "down actor description:" << actor_description << std::endl;
    std::cout << "down reason:" << caf::to_string(down_msg.reason) << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    counter_.RemoveActor(caf::actor_cast<caf::actor>(down_msg.source));

    StopMonitor(supervisor_, down_msg.source);
  }

  void InitWorkerNodes(
      const std::vector<actor_system::cluster::Member>& members,
      const std::string& host, uint16_t port) {
    std::cout << "self, host: " << host << std::endl;
    std::cout << "members size:" << members.size() << std::endl;
    for (auto& m : members) {
      std::cout << "member, host: " << m.host << std::endl;
      if (m.hostname == host) {
        continue;
      }
      std::cout << "add worker, host: " << m.hostname << std::endl;
      AddWorkerNode(m.host, k_yanghui_work_port1);
    }
  }

  void Update(const actor_system::cluster::Event& event) override {
    if (event.member.host != host_) {
      if (event.member.status == event.member.ActorSystemUp) {
        //         std::this_thread::sleep_for(std::chrono::seconds(2));
        AddWorkerNode(event.member.host, k_yanghui_work_port1);
        PrintClusterMembers();
      } else if (event.member.status == event.member.Down) {
        std::cout << "detect worker node down, host:" << event.member.host
                  << " port:" << event.member.port << std::endl;
      } else if (event.member.status == event.member.ActorSystemDown) {
        std::cout << "detect worker actor system down, host:"
                  << event.member.host << " port:" << event.member.port
                  << std::endl;
      }
    }
  }

  void PrintClusterMembers() {
    auto members = actor_system::cluster::Cluster::GetInstance()->GetMembers();
    std::cout << "Current Cluster Members:" << std::endl;
    for (int i = 0; i < members.size(); ++i) {
      auto& member = members[i];
      std::cout << "Member " << i + 1 << ": ";
      std::cout << "name: " << member.name << ", hostname: " << member.hostname
                << ", host: " << member.host << ", port:" << member.port
                << std::endl;
    }
  }

  void AddWorkerNode(const std::string& host, uint16_t port) {
    auto get_actor = system_.middleman().remote_actor(host, port);
    if (!get_actor) {
      std::cout << "connect remote actor failed. host: " << host
                << ", port:" << port
                << ", reason: " << to_string(get_actor.error()) << std::endl;
      return;
    }

    caf::scoped_actor self{system_};
    std::promise<AllActorData> promise;
    self->request(*get_actor, std::chrono::seconds(1), all_atom::value)
        .receive(
            [&](AllActorData ret) {
              promise.set_value(ret);
              std::cout << "=======add pool member host:" << host
                        << ", port:" << port << std::endl;
            },
            [&](caf::error err) {
              std::cout << "====== add work node Error. host : " << host
                        << ", port:" << port << std::endl;
              promise.set_exception(std::current_exception());
            });
    try {
      AllActorData actors = promise.get_future().get();
      for (auto work_actor : actors.actors) {
        counter_.AddActor(work_actor);
        SetMonitor(supervisor_, work_actor, "remote worker actor");
      }
    } catch (std::exception& e) {
      std::cout << "[exception caught: " << e.what() << "]" << std::endl;
    }
  }

  int AddNumber(int a, int b, int& result) {
    int error = 0;
    std::promise<int> promise;

    std::cout << "start add task input:" << a << ", " << b << std::endl;

    counter_.SendAndReceive([&](int ret) { promise.set_value(ret); },
                            [&](const caf::error& err) { error = 1; }, a, b);

    result = promise.get_future().get();

    std::cout << "get result:" << result << std::endl;
    return error;
  }

  int Compare(std::vector<int> numbers, int& min) {
    int error = 0;
    std::promise<int> promise;
    std::cout << "start compare task. input data:" << std::endl;

    for (int p : numbers) {
      std::cout << p << " ";
    }

    std::cout << std::endl;

    NumberCompareData send_data;
    send_data.numbers = numbers;

    counter_.SendAndReceive(
        [&](int ret) {
          min = ret;
          promise.set_value(ret);
        },
        [&](const caf::error& err) { error = 1; }, send_data);

    min = promise.get_future().get();
    std::cout << "get min:" << min << std::endl;

    return error;
  }

  caf::actor_system& system_;
  caf::actor supervisor_;
  std::string host_;
  uint16_t port_;
  uint16_t worker_port_;
  ActorUnion counter_;
};

caf::behavior getAllActors(caf::event_based_actor* self, AllActorData* actors,
                           std::mutex* mutex_) {
  return {[=](all_atom) -> AllActorData {
    std::cout << "get all actors" << std::endl;
    std::lock_guard<std::mutex> mutx(*mutex_);
    return *actors;
  }};
}

bool spawnAllActors(caf::actor_system& system,
                    ActorStatusMonitor& actor_status_monitor,
                    AllActorData& actors, std::mutex* mutex_) {
  auto actor1 = system.spawn<typed_calculator>();
  if (!actor1) {
    std::cout << "spawn actor1 failed." << std::endl;
    return false;
  }
  auto actor2 = system.spawn<typed_calculator>();
  if (!actor2) {
    std::cout << "spawn actor2 failed." << std::endl;
    return false;
  }
  auto actor3 = system.spawn<typed_calculator>();
  if (!actor3) {
    std::cout << "spawn actor3 failed." << std::endl;
    return false;
  }

  auto form_actor1 = caf::actor_cast<caf::actor>(actor1);
  auto form_actor2 = caf::actor_cast<caf::actor>(actor2);
  auto form_actor3 = caf::actor_cast<caf::actor>(actor3);

  actor_status_monitor.RegisterActor(form_actor1, "calculator1",
                                     "a actor can calculate for yanghui.");
  actor_status_monitor.RegisterActor(form_actor2, "calculator2",
                                     "a actor can calculate for yanghui.");
  actor_status_monitor.RegisterActor(form_actor3, "calculator3",
                                     "a actor can calculate for yanghui.");

  std::lock_guard<std::mutex> mutx(*mutex_);
  actors.actors.push_back(form_actor1);
  actors.actors.push_back(form_actor2);
  actors.actors.push_back(form_actor3);
  return true;
}

void shutdownAllActors(caf::scoped_actor& self, AllActorData& actors,
                       std::mutex* mutex_) {
  std::lock_guard<std::mutex> mutx(*mutex_);
  for (auto actor : actors.actors) {
    self->send_exit(actor, caf::exit_reason::user_shutdown);
  }
  actors.actors.clear();
}

void SmartWorkerStart(caf::actor_system& system, const config& cfg) {
  auto cluster = actor_system::cluster::Cluster::GetInstance();
  ActorStatusMonitor actor_status_monitor(system);
  ActorStatusServiceGprcImpl actor_status_service(system, actor_status_monitor);

  AllActorData actors;
  std::mutex mutex;
  spawnAllActors(system, actor_status_monitor, actors, &mutex);
  auto public_actor = system.spawn(getAllActors, &actors, &mutex);
  while (1) {
    std::cout << "*** try to publish actor..." << std::endl;
    auto expected_port =
        system.middleman().publish(caf::actor_cast<caf::actor>(public_actor),
                                   k_yanghui_work_port1, nullptr, true);
    if (!expected_port) {
      std::cout << "*** publish failed, error="
                << system.render(expected_port.error()) << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(2));
      continue;
    }

    break;
  }

  std::cout << "worker start at port:" << k_yanghui_work_port1 << std::endl;

  std::cout << "yanghui server ready to work, press 'q' to stop." << std::endl;
  actor_status_service.Run();
  cluster->NotifyReady();

  // start compute
  while (true) {
    std::string dummy;
    std::getline(std::cin, dummy);
    if (dummy == "q") {
      std::cout << "stop work" << std::endl;
      break;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  caf::scoped_actor self{system};
  system.middleman().unpublish(public_actor, k_yanghui_work_port1);
  shutdownAllActors(self, actors, &mutex);
}

caf::behavior yanghui(caf::event_based_actor* self, CountCluster* counter) {
  return {
      [=](const std::vector<std::vector<int>>& data) {
        int n = data.size();
        //        int temp_states[n];
        //        int states[n];
        int* temp_states = reinterpret_cast<int*>(malloc(sizeof(int) * n));
        int* states = reinterpret_cast<int*>(malloc(sizeof(int) * n));
        int error = 0;

        states[0] = 1;
        states[0] = data[0][0];
        int i, j, k, min_sum = INT_MAX;
        for (i = 1; i < n; i++) {
          for (j = 0; j < i + 1; j++) {
            if (j == 0) {
              // temp_states[0] = states[0] + data[i][j];
              error = counter->AddNumber(states[0], data[i][j], temp_states[0]);
              if (0 != error) {
                caf::aout(self) << "cluster down, exit task" << std::endl;
                return INT_MAX;
              }
            } else if (j == i) {
              // temp_states[j] = states[j - 1] + data[i][j];
              error =
                  counter->AddNumber(states[j - 1], data[i][j], temp_states[j]);
              if (0 != error) {
                caf::aout(self) << "cluster down, exit task" << std::endl;
                return INT_MAX;
              }
            } else {
              // temp_states[j] = std::min(states[j - 1], states[j]) +
              // data[i][j];
              error = counter->AddNumber(std::min(states[j - 1], states[j]),
                                         data[i][j], temp_states[j]);
              if (0 != error) {
                caf::aout(self) << "cluster down, exit task" << std::endl;
                return INT_MAX;
              }
            }
          }

          for (k = 0; k < i + 1; k++) {
            states[k] = temp_states[k];
          }
        }

        //    for (j = 0; j < n; j++) {
        //      if (states[j] < min_sum) min_sum = states[j];
        //    }

        std::vector<int> states_vec(states, states + n);

        error = counter->Compare(states_vec, min_sum);
        if (0 != error) {
          caf::aout(self) << "cluster down, exit task" << std::endl;
          return INT_MAX;
        }

        caf::aout(self) << "yanghui triangle actor task complete, result: "
                        << min_sum << std::endl;
        free(temp_states);
        free(states);
        return min_sum;
      },
      [=](std::string&) {
        caf::aout(self) << "simulate get a critical error， yanghui actor quit."
                        << std::endl;
        self->quit();
        return 0;
      }};
}

// struct yanghui_job_state {
//  int count = 0;
//};
//
// struct yanghui_job_result {
//
//};
//
// caf::behavior yanghui_jobs(
//    caf::stateful_actor<yanghui_job_state>* self, const caf::actor& buddy1,
//    const caf::actor& buddy2) {
//  return {[=](const std::vector<std::vector<int>>& triangle_data) {
//            self->send(buddy1, triangle_data);
//          },
//          [=](int result) {
//            self->state.count++;
//            if (self->state.count == 2) {
//
//            }
//          }};
//};

struct yanghui_state {
  int level_ = 1;
  int count_ = 0;
  std::vector<std::vector<int>> triangle_data_;
  std::vector<int> last_level_results_;
  caf::strong_actor_ptr triangle_sender_;
};

using start_atom = caf::atom_constant<caf::atom("start")>;
using end_atom = caf::atom_constant<caf::atom("end")>;

caf::behavior yanghui_with_priority(caf::stateful_actor<yanghui_state>* self,
                                    WorkerPool* worker_pool,
                                    bool is_high_priority = false) {
  return {
      [=](const std::vector<std::vector<int>>& triangle_data) {
        std::cout << "ready to receive triangle data" << std::endl;
        self->state.triangle_sender_ = self->current_sender();
        self->state.last_level_results_ =
            std::vector<int>(triangle_data.size(), 0);
        self->state.last_level_results_[0] = triangle_data[0][0];
        for (int k = 0; k < triangle_data.size(); k++) {
          self->state.triangle_data_.emplace_back(triangle_data[k]);
        }
        self->send(self, start_atom::value);
        std::cout << "already receive triangle data" << std::endl;
      },
      [=](start_atom) {
        int i = self->state.level_;
        for (int j = 0; j < i + 1; j++) {
          std::cout << "start level:" << j << std::endl;
          auto worker = caf::actor_cast<calculator>(worker_pool->GetWorker());
          if (j == 0) {
            std::cout << "start atom: 1" << std::endl;
            if (is_high_priority) {
              self->send<caf::message_priority::high>(
                  worker, self->state.last_level_results_[0],
                  self->state.triangle_data_[i][j], j);
            } else {
              self->send(worker, self->state.last_level_results_[0],
                         self->state.triangle_data_[i][j], j);
            }
          } else if (j == i) {
            std::cout << "start atom: 2" << std::endl;
            if (is_high_priority) {
              self->send<caf::message_priority::high>(
                  worker, self->state.last_level_results_[j - 1],
                  self->state.triangle_data_[i][j], j);
            } else {
              self->send(worker, self->state.last_level_results_[j - 1],
                         self->state.triangle_data_[i][j], j);
            }
          } else {
            std::cout << "start atom: 3" << std::endl;
            if (is_high_priority) {
              self->send<caf::message_priority::high>(
                  worker,
                  std::min(self->state.last_level_results_[j - 1],
                           self->state.last_level_results_[j]),
                  self->state.triangle_data_[i][j], j);
            } else {
              self->send<caf::message_priority::normal>(
                  worker,
                  std::min(self->state.last_level_results_[j - 1],
                           self->state.last_level_results_[j]),
                  self->state.triangle_data_[i][j], j);
            }
          }
        }
        std::cout << "start atom: end" << std::endl;
      },
      [=](std::string& result_with_position) {
        std::cout << "result with position: " << result_with_position
                  << std::endl;

        int index = result_with_position.find(":");
        std::cout << "result string: " << result_with_position.substr(0, index)
                  << std::endl;
        std::cout << "position string: "
                  << result_with_position.substr(
                         index + 1, result_with_position.size() - index)
                  << std::endl;
        int result = std::stoi(result_with_position.substr(0, index));
        int position = std::stoi(result_with_position.substr(
            index + 1, result_with_position.size() - index));
        self->state.last_level_results_[position] = result;
        std::cout << "position " << position << ":" << result << std::endl;
        self->state.count_++;
        std::cout << "get level result:1" << std::endl;
        if (self->state.level_ == self->state.count_ - 1) {
          std::cout << "get level result2" << std::endl;
          if (self->state.level_ == self->state.triangle_data_.size() - 1) {
            self->send(self, end_atom::value);
            std::cout << "get level result3" << std::endl;
          } else {
            self->state.level_++;
            self->state.count_ = 0;
            self->send(self, start_atom::value);
            std::cout << "get level result4" << std::endl;
          }
        }
      },
      [=](end_atom) {
        NumberCompareData send_data;
        send_data.numbers = self->state.last_level_results_;
        auto worker = caf::actor_cast<calculator>(worker_pool->GetWorker());
        std::cout << "end atom:1" << std::endl;
        self->request(worker, caf::infinite, send_data)
            .await([=](int final_result) {
              if (is_high_priority) {
                caf::aout(self)
                    << "high priority final result: " << final_result
                    << std::endl;
              } else {
                caf::aout(self)
                    << "normal priority final result: " << final_result
                    << std::endl;
              }

              if (is_high_priority) {
                std::cout << "end atom:2" << std::endl;
                self->send<caf::message_priority::high>(
                    caf::actor_cast<caf::actor>(self->state.triangle_sender_),
                    final_result);
              } else {
                std::cout << "end atom:2" << std::endl;
                self->send<caf::message_priority::normal>(
                    caf::actor_cast<caf::actor>(self->state.triangle_sender_),
                    final_result);
              }
            });
      }};
}

std::vector<std::vector<int>> kYanghuiData2 = {
    {5}, {7, 8}, {2, 1, 4}, {4, 2, 6, 1}, {2, 7, 3, 4, 5}, {2, 3, 7, 6, 8, 3}};

void printRet(int return_value) {
  printf("call actor return value: %d\n", return_value);
  // std::cout << "call actor return value:" << return_value << std::endl;
}

void dealSendErr(const caf::error& err) {
  std::cout << "call actor get error:" << caf::to_string(err) << std::endl;
}

void SmartRootStart(caf::actor_system& system, const config& cfg) {
  CountCluster counter(cfg.root_host, system, cfg.node_keeper_port,
                       cfg.worker_port);

  // local test
  //  counter.AddWorkerNode("localhost", k_yanghui_work_port1);
  //  counter.AddWorkerNode("localhost", k_yanghui_work_port2);
  //  counter.AddWorkerNode("localhost", k_yanghui_work_port3);

  ActorStatusMonitor actor_status_monitor(system);
  ActorStatusServiceGprcImpl actor_status_service(system, actor_status_monitor);

  auto yanghui_actor = system.spawn(yanghui, &counter);
  actor_status_monitor.RegisterActor(yanghui_actor, "Yanghui",
                                     "a actor can count yanghui triangle.");

  std::cout << "yanghui server ready to work, press 'n' to go, 'q' to stop"
            << std::endl;

  ActorGuard actor_guard(
      yanghui_actor,
      [&](std::atomic<bool>& active) {
        active = true;
        auto new_yanghui = system.spawn(yanghui, &counter);
        actor_status_monitor.RegisterActor(
            yanghui_actor, "Yanghui", "a actor can count yanghui triangle.");
        // SetMonitor(supervisor, yanghui_actor, "worker actor for testing");
        return new_yanghui;
      },
      system);

  actor_status_service.Run();
  counter.GetInstance()->NotifyReady();

  // start compute
  while (true) {
    std::string dummy;
    std::getline(std::cin, dummy);
    if (dummy == "q") {
      std::cout << "stop work" << std::endl;
      break;
    }

    if (dummy == "n") {
      std::cout << "start count." << std::endl;
      // self->send(yanghui_actor, kYanghuiData2);
      actor_guard.SendAndReceive(printRet, dealSendErr, kYanghuiData2);

      continue;
    }

    if (dummy == "e") {
      std::cout << "start count." << std::endl;
      // self->send(yanghui_actor, kYanghuiData2);
      actor_guard.SendAndReceive(printRet, dealSendErr, "quit");

      continue;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void StupidRootStart(caf::actor_system& system, const config& cfg) {
  WorkerPool worker_pool(system, cfg.root_host, cfg.worker_port);
  worker_pool.Init();

  auto yanghui_actor_normal_priority =
      system.spawn(yanghui_with_priority, &worker_pool, false);
  auto yanghui_actor_high_priority =
      system.spawn(yanghui_with_priority, &worker_pool, true);

  std::cout << "yanghui_actor_normal_priority id: "
            << yanghui_actor_normal_priority.id() << std::endl;
  std::cout << "yanghui_actor_high_priority id: "
            << yanghui_actor_high_priority.id() << std::endl;

  std::cout << "yanghui server ready to work, press 'n' to go, 'q' to stop"
            << std::endl;
  while (true) {
    std::cout << "waiting for worker" << std::endl;
    if (!worker_pool.IsEmpty()) {
      break;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  caf::scoped_actor self{system};
  std::cout << "ready for scoped actor" << std::endl;

  auto worker1 = worker_pool.GetWorker();
  auto worker2 = worker_pool.GetWorker();

  auto f1 = caf::make_function_view(caf::actor_cast<calculator>(worker1));
  std::cout << "received result: " << f1(1, 2) << std::endl;
  auto f2 = caf::make_function_view(caf::actor_cast<calculator>(worker2));
  std::cout << "received result: " << f2(2, 3) << std::endl;

  self->send(yanghui_actor_normal_priority, kYanghuiData2);
  self->send(yanghui_actor_high_priority, kYanghuiData2);
  std::cout << "send message to two yanghui actors" << std::endl;

  actor_system::cluster::Cluster::GetInstance()->NotifyReady();
  while (true) {
    std::string dummy;
    std::getline(std::cin, dummy);
    std::cout << "in the loop, waiting for q" << std::endl;
    if (dummy == "q") {
      std::cout << "stop work" << std::endl;
      break;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "end loop" << std::endl;
  }
}

void StupidWorkerStart(caf::actor_system& system, const config& cfg) {
  system.middleman().open(cfg.worker_port, nullptr, true);
  actor_system::cluster::Cluster::GetInstance()->NotifyReady();
  while (true) {
    std::string dummy;
    std::getline(std::cin, dummy);
    if (dummy == "q") {
      std::cout << "stop work" << std::endl;
      break;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

void caf_main(caf::actor_system& system, const config& cfg) {
  if (cfg.root) {
    StupidRootStart(system, cfg);
  } else {
    StupidWorkerStart(system, cfg);
  }
}

CAF_MAIN(caf::io::middleman)
