#pragma once
#include "Common.h"
#include "StringUtil.hpp"

#include <fmt/format.h>
#include <folly/CancellationToken.h>
#include <folly/MPMCPipeline.h>
#include <folly/MPMCQueue.h>

#include <iostream>
#include <thread>

enum class OutputType { Normal, Error };
enum class OutputColor { Normal, Green, Red, Yellow };

struct Output {
  Output() = default;
  Output(String message, OutputType type = OutputType::Normal)
      : message(std::move(message)), type(type),
        color(type == OutputType::Error ? OutputColor::Red
                                        : OutputColor::Normal) {}

  Output(String message, OutputColor color)
      : message(std::move(message)), type(OutputType::Normal), color(color) {}

  Output(String message, OutputType type, OutputColor color)
      : message(std::move(message)), type(type), color(color) {}

  CRU_DEFAULT_COPY(Output)
  CRU_DEFAULT_MOVE(Output)
  ~Output() = default;

  String message;
  OutputType type;
  OutputColor color;
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

template <typename... Args>
void SendOutput(OutputColor color, StringView format, Args &&...args) {
  output_queue.blockingWrite(
      Output{fmt::format(format, std::forward<Args>(args)...), color});
}

void SignalAndWaitForOutputThreadStop();

void OnInputLine(StringView line);

void StartIOThread();
