#include "Mutex.h"

#include <cassert>

#ifndef CRU_WINDOWS
#include <errno.h>
#endif

namespace cru {
Mutex::Mutex() {
#ifdef CRU_WINDOWS
  handle_ = CreateMutexW(nullptr, FALSE, nullptr);
  assert(handle_);
#else
  mutex_ = std::make_unique<pthread_mutex_t>();

  auto c = pthread_mutex_init(mutex_.get(), nullptr);
  assert(c == 0);
#endif
}

Mutex::Mutex(Mutex &&other)
#ifdef CRU_WINDOWS
    : handle_(other.handle_)
#else
    : mutex_(std::move(other.mutex_))
#endif
{
#ifdef CRU_WINDOWS
  other.handle_ = nullptr;
#endif
}

Mutex &Mutex::operator=(Mutex &&other) {
  if (this != &other) {
    Destroy();
#ifdef CRU_WINDOWS
    handle_ = other.handle_;
    other.handle_ = nullptr;
#else
    mutex_ = std::move(other.mutex_);
#endif
  }
  return *this;
}

Mutex::~Mutex() { Destroy(); }

void Mutex::Lock() {
#ifdef CRU_WINDOWS
  auto c = WaitForSingleObject(handle_, INFINITE);
  assert(c == WAIT_OBJECT_0);
#else
  assert(mutex_);
  auto c = pthread_mutex_lock(mutex_.get());
  assert(c == 0);
#endif
}

bool Mutex::TryLock() {
#ifdef CRU_WINDOWS
  auto c = WaitForSingleObject(handle_, 0);
  assert(c == WAIT_OBJECT_0 || c == WAIT_TIMEOUT);
  return c == WAIT_OBJECT_0 ? true : false;
#else
  assert(mutex_);
  auto c = pthread_mutex_trylock(mutex_.get());
  assert(c == 0 || c == EBUSY);
  return c == 0 ? true : false;
#endif
}

void Mutex::Unlock() {
#ifdef CRU_WINDOWS
  auto c = ReleaseMutex(handle_);
  assert(c);
#else
  assert(mutex_);
  auto c = pthread_mutex_unlock(mutex_.get());
  assert(c == 0);
#endif
}

void Mutex::Destroy() {
#ifdef CRU_WINDOWS
  if (handle_ != nullptr) {
    auto c = CloseHandle(handle_);
    assert(c);
  }
#else
  if (mutex_ != nullptr) {
    auto c = pthread_mutex_destroy(mutex_.get());
    assert(c);
    mutex_ = nullptr;
  }
#endif
}

} // namespace cru
