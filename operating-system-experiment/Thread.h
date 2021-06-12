#ifndef HEADER_THREAD_H
#define HEADER_THREAD_H

#include "Base.h"

#ifdef CRU_WINDOWS
#include <Windows.h>
#else
#include <pthread.h>
#endif

#ifdef __cplusplus

#include <cassert>
#include <functional>
#include <memory>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace cru {
class CRU_API Thread {
public:
  Thread() = default;
  template <typename Fn, typename... Args> Thread(Fn &&process, Args &&...args);
  Thread(const Thread &other) = delete;
  Thread(Thread &&other) noexcept;
  Thread &operator=(const Thread &other) = delete;
  Thread &operator=(Thread &&other) noexcept;
  ~Thread();

public:
  void Join();
  void Detach();

#ifdef CRU_WINDOWS
  DWORD
#else
  pthread_t
#endif
  GetNativeID();

#ifdef CRU_WINDOWS
  HANDLE
#else
  pthread_t
#endif
  GetNativeHandle();

  void swap(Thread &other) noexcept;

private:
  void Destroy() noexcept;
  void CreateThread(std::function<void()> *proc);

private:
  bool detached_ = false;
  bool joined_ = false;

#ifdef CRU_WINDOWS
  DWORD thread_id_ = 0;
  HANDLE thread_handle_ = nullptr;
#else
  std::unique_ptr<pthread_t> thread_;
#endif
};

template <typename Fn, typename... Args>
Thread::Thread(Fn &&process, Args &&...args) {
  std::tuple<std::decay_t<Args>...> a{std::forward<Args>(args)...};
  auto p = new std::function<void()>(
      [process = std::forward<Fn>(process), args = std::move(a)]() {
        std::apply(process, std::move(args));
      });

  CreateThread(p);
};
} // namespace cru

#endif

#endif
