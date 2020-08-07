/*
 * Copyright (c) 2020 ThoughtWorks Inc.
 */

#include "./logger.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

std::vector<spdlog::sink_ptr> GenerateSinks(const CDCFConfig& config);

TEST(GenerateSinksTest,
     should_sinks_have_only_console_sink_given_default_config) {
  CDCFConfig config;
  auto sinks = GenerateSinks(config);

  EXPECT_EQ(1, sinks.size());
}

TEST(GenerateSinksTest,
     should_sinks_have_no_console_sink_given_log_to_config_is_false) {
  CDCFConfig config;
  config.no_log_to_console_ = true;

  auto sinks = GenerateSinks(config);

  EXPECT_EQ(0, sinks.size());
}

TEST(GenerateSinksTest, should_sinks_have_file_sink_given_log_file_not_empty) {
  CDCFConfig config;
  config.no_log_to_console_ = true;
  config.log_file_ = "cdcf.log";

  auto sinks = GenerateSinks(config);

  EXPECT_EQ(1, sinks.size());
}

TEST(GenerateSinksTest,
     should_sinks_have_rotating_sink_given_log_file_size_in_bytes_not_0) {
  CDCFConfig config;
  config.no_log_to_console_ = true;
  config.log_file_ = "cdcf.log";
  config.log_file_size_in_bytes_ = 1024;

  auto sinks = GenerateSinks(config);

  EXPECT_EQ(1, sinks.size());
}

TEST(GenerateSinksTest,
     should_sinks_have_console_and_file_sink_given_correct_config) {
  CDCFConfig config;
  config.log_file_ = "cdcf.log";

  auto sinks = GenerateSinks(config);

  EXPECT_EQ(2, sinks.size());
}

TEST(GenerateSinksTest,
     should_sinks_have_console_and_rotating_sink_given_correct_config) {
  CDCFConfig config;
  config.log_file_ = "cdcf.log";
  config.log_file_size_in_bytes_ = 1024;

  auto sinks = GenerateSinks(config);

  EXPECT_EQ(2, sinks.size());
}

TEST(LoggerTest, should_log_to_console_correctly_given_default_config) {
  testing::internal::CaptureStdout();
  CDCFConfig config;
  cdcf::Logger::Init(config);

  CDCF_LOGGER_DEBUG("Debug Log");
  CDCF_LOGGER_INFO("Hello World");

  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_THAT(output, testing::HasSubstr("Hello World"));
  EXPECT_THAT(output, testing::HasSubstr("info"));
  EXPECT_THAT(output, testing::HasSubstr("logger_test.cc:"));
  EXPECT_TRUE(output.find("Debug Log") == std::string::npos);
}
