/*
 * Copyright (c) 2020 ThoughtWorks Inc.
 */

#include "include/yanghui_actor.h"

#include <limits.h>

#include <algorithm>
#include <string>
#include <vector>

#include "cdcf/logger.h"
caf::behavior yanghui(caf::event_based_actor* self,
                      counter_interface* counter) {
  return {
      [=](const std::vector<std::vector<int>>& data) {
        int n = static_cast<int>(data.size());
        std::vector<int> temp_states;
        temp_states.resize(n);
        std::vector<int> states;
        states.resize(n);
        int error = 0;
        CDCF_LOGGER_INFO(
            "yanghui actor receive data, start count. actor address:{}.",
            caf::to_string(self->address()));

        states[0] = 1;
        states[0] = data[0][0];
        int i, j, k, min_sum = INT_MAX;
        for (i = 1; i < n; i++) {
          for (j = 0; j < i + 1; j++) {
            if (j == 0) {
              // temp_states[0] = states[0] + data[i][j];
              error = counter->AddNumber(states[0], data[i][j], temp_states[0]);
              if (0 != error) {
                CDCF_LOGGER_ERROR("add task error:{}, input:{}, {}", error,
                                  states[0], data[i][j]);
                return INT_MAX;
              }
            } else if (j == i) {
              // temp_states[j] = states[j - 1] + data[i][j];
              error =
                  counter->AddNumber(states[j - 1], data[i][j], temp_states[j]);
              if (0 != error) {
                CDCF_LOGGER_ERROR("add task error:{}, input:{}, {}", error,
                                  states[j - 1], data[i][j]);
                return INT_MAX;
              }
            } else {
              // temp_states[j] = std::min(states[j - 1], states[j]) +
              // data[i][j];
              error = counter->AddNumber(std::min(states[j - 1], states[j]),
                                         data[i][j], temp_states[j]);
              if (0 != error) {
                CDCF_LOGGER_ERROR("add task error:{}, input:{}, {}, {}", error,
                                  states[j], data[i][j], data[i][j]);
                return INT_MAX;
              }
            }
          }

          for (k = 0; k < i + 1; k++) {
            states[k] = temp_states[k];
          }
        }

        error = counter->Compare(states, min_sum);
        if (0 != error) {
          CDCF_LOGGER_ERROR("compare task failed.");
          return INT_MAX;
        }

        CDCF_LOGGER_INFO("yanghui triangle actor task complete, result:{}",
                         min_sum);
        return min_sum;
      },
      [=](std::string&) {
        CDCF_LOGGER_ERROR("simulate get a critical error, yanghui actor quit.");
        self->quit();
        return 0;
      }};
}
