/*
 * Copyright (c) 2020 ThoughtWorks Inc.
 */

#include "include/yanghui_demo_calculator.h"

calculator::behavior_type sleep_calculator_fun(calculator::pointer self,
                                               std::atomic_int& deal_msg_count,
                                               int sleep_micro) {
  return {
      [self, &deal_msg_count, sleep_micro](int a, int b) -> int {
        ++deal_msg_count;
        CDCF_LOGGER_INFO(
            " slow calculator received add task. input a: {} b: {},  "
            "************* calculator sleep microseconds: {} msg count:{}",
            a, b, sleep_micro, deal_msg_count);
        //        caf::aout(self) << " slow calculator received add task. input
        //        a:" << a
        //                        << " b:" << b
        //                        << ", ************* calculator sleep
        //                        microseconds:"
        //                        << sleep_micro << " msg count:" <<
        //                        deal_msg_count
        //                        << std::endl;
        if (sleep_micro) {
          std::this_thread::sleep_for(std::chrono::microseconds(sleep_micro));
        }

        int result = a + b;
        CDCF_LOGGER_INFO("return: {}", result);
        // caf::aout(self) << "return: " << result << std::endl;
        return result;
      },
      [=](int a, int b, int position) -> ResultWithPosition {
        return ResultWithPosition();
      },
      [self, &deal_msg_count, sleep_micro](NumberCompareData& data) -> int {
        ++deal_msg_count;
        if (data.numbers.empty()) {
          CDCF_LOGGER_ERROR("get empty compare");
          // caf::aout(self) << "get empty compare" << std::endl;
          return 999;
        }

        int result = data.numbers[0];

        CDCF_LOGGER_INFO("received compare task, input: ");
        // caf::aout(self) << "received compare task, input: ";

        for (int number : data.numbers) {
          caf::aout(self) << number << " ";
          if (number < result) {
            result = number;
          }
        }
        CDCF_LOGGER_INFO(
            "************* calculator sleep microseconds:"
            "{} msg count: {}",
            sleep_micro, deal_msg_count);
        //        caf::aout(self) << "************* calculator sleep
        //        microseconds:"
        //                        << sleep_micro << " msg count:" <<
        //                        deal_msg_count
        //                        << std::endl;

        if (sleep_micro) {
          std::this_thread::sleep_for(std::chrono::microseconds(sleep_micro));
        }
        CDCF_LOGGER_INFO("return: {}", result);
        // caf::aout(self) << "return: " << result << std::endl;

        return result;
      }};
}

calculator::behavior_type calculator_fun(calculator::pointer self) {
  return {[=](int a, int b) -> int {
            caf::aout(self) << "received add task. input a:" << a << " b:" << b
                            << std::endl;

            int result = a + b;
            caf::aout(self) << "return: " << result << std::endl;
            return result;
          },
          [=](int a, int b, int position) -> ResultWithPosition {
            return ResultWithPosition();
          },
          [=](NumberCompareData& data) -> int {
            if (data.numbers.empty()) {
              caf::aout(self) << "get empty compare" << std::endl;
              return 999;
            }

            int result = data.numbers[0];

            caf::aout(self) << "received compare task, input: ";

            for (int number : data.numbers) {
              caf::aout(self) << number << " ";
              if (number < result) {
                result = number;
              }
            }

            caf::aout(self) << std::endl;
            caf::aout(self) << "return: " << result << std::endl;

            return result;
          }};
}

bool operator==(const NumberCompareData& lhs, const NumberCompareData& rhs) {
  return lhs.numbers == rhs.numbers && lhs.index == rhs.index;
}
std::ostream& operator<<(std::ostream& os, const NumberCompareData& data) {
  os << "numbers: ";
  for (auto& x : data.numbers) {
    os << x << " ";
  }
  os << " index: " << data.index;
  return os;
}

caf::behavior CalculatorWithPriority::make_behavior() {
  return {[=](int a, int b) -> int {
            caf::aout(this) << "received add task. input a:" << a << " b:" << b
                            << std::endl;

            int result = a + b;
            caf::aout(this) << "return: " << result << std::endl;
            return result;
          },
          [=](int a, int b, int position) -> ResultWithPosition {
            if (this->current_message_id().is_urgent_message()) {
              caf::aout(this)
                  << "received high priority add task. input a:" << a
                  << " b:" << b << std::endl;
            } else {
              caf::aout(this)
                  << "received normal priority add task. input a:" << a
                  << " b:" << b << std::endl;
            }
            ResultWithPosition result = {a + b, position};

            auto start = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds =
                std::chrono::milliseconds(0);
            std::chrono::duration<double> time_limit =
                std::chrono::milliseconds(100);
            while (elapsed_seconds < time_limit) {
              auto end = std::chrono::steady_clock::now();
              elapsed_seconds = end - start;
            }

            std::cout << "return: " << result.result << std::endl;
            return result;
          },
          [=](NumberCompareData& data) -> int {
            if (data.numbers.empty()) {
              caf::aout(this) << "get empty compare" << std::endl;
              return 999;
            }

            int result = data.numbers[0];

            caf::aout(this) << "received compare task, input: ";

            for (int number : data.numbers) {
              caf::aout(this) << number << " ";
              if (number < result) {
                result = number;
              }
            }

            caf::aout(this) << std::endl;
            caf::aout(this) << "return: " << result << std::endl;

            return result;
          }};
}
