#include "Thread.h"

#include <cassert>
#include <exception>
#include <utility>

namespace cru {
Thread::Thread(Thread &&other) noexcept
    : joined_(other.joined_), thread_handle_(other.thread_handle_) {
  other.joined_ = false;
  other.thread_handle_ = nullptr;
}

Thread &Thread::operator=(Thread &&other) noexcept {
  if (this != &other) {
    joined_ = other.joined_;
    thread_handle_ = other.thread_handle_;
    other.joined_ = false;
    other.thread_handle_ = nullptr;
  }

  return *this;
}

Thread::~Thread() { Destroy(); }

void Thread::Join() {
  assert(thread_handle_);
  joined_ = true;
  WaitForSingleObject(thread_handle_, INFINITE);
}

void Thread::Detach() {
  assert(thread_handle_);
  detached_ = true;
}

void Thread::swap(Thread &other) noexcept {
#ifdef CRU_WINDOWS
  Thread temp = std::move(*this);
  *this = std::move(other);
  other = std::move(temp);
#else
#endif
}

void Thread::Destroy() noexcept {
  if (!detached_ && !joined_ && thread_handle_ != nullptr) {
    std::terminate();
  } else {
    joined_ = false;
    thread_handle_ = nullptr;
  }
}

namespace details {
#ifdef CRU_WINDOWS
DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter) {
  auto p = static_cast<std::function<void()> *>(lpParameter);
  (*p)();
  delete p;
  return 0;
}
#else
#endif
} // namespace details
} // namespace cru