#pragma once
#include "StringUtil.hpp"

#include <iostream>

#include <fmt/format.h>
#include <folly/MPMCPipeline.h>
#include <folly/MPMCQueue.h>

enum class OutputType { Normal, Error };

struct Output {
  Output() = default;
  Output(std::wstring message, OutputType type = OutputType::Normal)
      : message(std::move(message)), type(type) {}

  CRU_DEFAULT_COPY(Output)
  CRU_DEFAULT_MOVE(Output)
  ~Output() = default;

  std::wstring message;
  OutputType type;
};

extern folly::MPMCQueue<Output> output_queue;

inline void SendOutput(Output output) {
  output_queue.blockingWrite(std::move(output));
}

inline void SendOutput(std::wstring output) {
  SendOutput(std::move(output));
}

template <typename... Args>
void SendOutput(std::wstring_view format, Args &&...args) {
  output_queue.blockingWrite(fmt::format(format, std::forward<Args>(args)...));
}

template <typename... Args>
void SendOutput(OutputType type, std::wstring_view format, Args &&...args) {
  output_queue.blockingWrite(
      Output{fmt::format(format, std::forward<Args>(args)...), type});
}

void OutputThread();
