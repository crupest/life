#pragma once
#include "Common.h"
#include "StringUtil.hpp"

#include <fmt/format.h>
#include <folly/MPMCPipeline.h>
#include <folly/MPMCQueue.h>

#include <iostream>

enum class OutputType { Normal, Error };

struct Output {
  Output() = default;
  Output(String message, OutputType type = OutputType::Normal)
      : message(std::move(message)), type(type) {}

  CRU_DEFAULT_COPY(Output)
  CRU_DEFAULT_MOVE(Output)
  ~Output() = default;

  String message;
  OutputType type;
};

extern folly::MPMCQueue<Output> output_queue;

inline void SendOutput(Output output) {
  output_queue.blockingWrite(std::move(output));
}

inline void SendOutput(String output) { SendOutput(Output{std::move(output)}); }

template <typename... Args> void SendOutput(StringView format, Args &&...args) {
  output_queue.blockingWrite(fmt::format(format, std::forward<Args>(args)...));
}

template <typename... Args>
void SendOutput(OutputType type, StringView format, Args &&...args) {
  output_queue.blockingWrite(
      Output{fmt::format(format, std::forward<Args>(args)...), type});
}

void OutputThread();
