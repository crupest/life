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
#include <tuple>

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

  void swap(Thread &other) noexcept;

private:
  void Destroy() noexcept;

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

namespace details {
#ifdef CRU_WINDOWS
CRU_API DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter);
#else
void *ThreadProc(void *data);
#endif
} // namespace details

template <typename Fn, typename... Args>
Thread::Thread(Fn &&process, Args &&...args) {
  std::tuple<std::decay_t<Args>...> a{std::forward<Args>(args)...};
  auto p = new std::function<void()>(
      [process = std::forward<Fn>(process), args = std::move(a)]() {
        std::apply(process, std::move(args));
      });

#ifdef CRU_WINDOWS
  thread_handle_ = ::CreateThread(nullptr, 0, &::cru::details::ThreadProc,
                                  static_cast<void *>(p), 0, &thread_id_);
  assert(thread_handle_);
#else
  thread_.reset(new pthread_t());
  auto c = pthread_create(thread_.get(), nullptr, details::ThreadProc,
                          static_cast<void *>(p));
  assert(c == 0);
#endif
};
} // namespace cru

#endif

#endif