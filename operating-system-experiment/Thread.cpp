#include "Thread.h"

#include <cassert>
#include <exception>
#include <utility>

namespace cru {
Thread::Thread(Thread &&other) noexcept
    : detached_(other.detached_), joined_(other.joined_),
#ifdef CRU_WINDOWS
      thread_handle_(other.thread_handle_)
#else
      thread_(std::move(other.thread_))
#endif
{
  other.joined_ = false;
#ifdef CRU_WINDOWS
  other.thread_handle_ = nullptr;
#endif
} // namespace cru

Thread &Thread::operator=(Thread &&other) noexcept {
  if (this != &other) {
    detached_ = other.detached_;
    joined_ = other.joined_;
#ifdef CRU_WINDOWS
    thread_handle_ = other.thread_handle_;
    other.thread_handle_ = nullptr;
#else
    thread_ = std::move(other.thread_);
#endif
    other.detached_ = false;
    other.joined_ = false;
  }

  return *this;
}

Thread::~Thread() { Destroy(); }

void Thread::Join() {
  joined_ = true;
#ifdef CRU_WINDOWS
  assert(thread_handle_);
  WaitForSingleObject(thread_handle_, INFINITE);
#else
  assert(thread_);
  auto c = pthread_join(*thread_, nullptr);
  assert(c == 0);
#endif
}

void Thread::Detach() {
#ifdef CRU_WINDOWS
  assert(thread_handle_);
#else
  assert(thread_);
#endif
  detached_ = true;
}

#ifdef CRU_WINDOWS
DWORD
#else
pthread_t
#endif
Thread::GetNativeID() {
#ifdef CRU_WINDOWS
  assert(thread_handle_);
  return thread_id_;
#else
  assert(thread_);
  return *thread_;
#endif
}

#ifdef CRU_WINDOWS
HANDLE
#else
pthread_t
#endif
Thread::GetNativeHandle() {
#ifdef CRU_WINDOWS
  assert(thread_handle_);
  return thread_handle_;
#else
  assert(thread_);
  return *thread_;
#endif
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
  if (!detached_ && !joined_ &&
#ifdef CRU_WINDOWS
      thread_handle_ != nullptr
#else
      thread_ != nullptr
#endif
  ) {
    std::terminate();
  } else {
    detached_ = false;
    joined_ = false;
#ifdef CRU_WINDOWS
    thread_id_ = 0;
    if (thread_handle_ != nullptr) {
      CloseHandle(thread_handle_);
      thread_handle_ = nullptr;
    }
#else
    thread_ = nullptr;
#endif
  }
}

namespace {
#ifdef CRU_WINDOWS
DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter) {
  auto p = static_cast<std::function<void()> *>(lpParameter);
  (*p)();
  delete p;
  return 0;
}
#else
void *ThreadProc(void *data) {
  auto p = static_cast<std::function<void()> *>(data);
  (*p)();
  delete p;
  return nullptr;
}

#endif
} // namespace

void Thread::CreateThread(std::function<void()> *proc) {
#ifdef CRU_WINDOWS
  thread_handle_ = ::CreateThread(nullptr, 0, ThreadProc,
                                  static_cast<void *>(proc), 0, &thread_id_);
  assert(thread_handle_);
#else
  thread_.reset(new pthread_t());
  auto c = pthread_create(thread_.get(), nullptr, ThreadProc,
                          static_cast<void *>(proc));
  assert(c == 0);
#endif
};

} // namespace cru