#include "Mutex.h"

#include <cassert>
#include <pthread.h>

#ifndef CRU_WINDOWS
#include <errno.h>
#endif

namespace cru {
Mutex::Mutex() {
#ifdef CRU_WINDOWS
#else
  mutex_ = std::make_unique<pthread_mutex_t>();

  auto c = pthread_mutex_init(mutex_.get(), nullptr);
  assert(c == 0);
#endif
}

Mutex::Mutex(Mutex &&other)
#ifdef CRU_WINDOWS
#else
    : mutex_(std::move(other.mutex_))
#endif
{
}

Mutex &Mutex::operator=(Mutex &&other) {
  if (this != &other) {
    Destroy();
    mutex_ = std::move(other.mutex_);
  }
  return *this;
}

Mutex::~Mutex() { Destroy(); }

void Mutex::Lock() {
#ifdef CRU_WINDOWS
#else
  assert(mutex_);
  auto c = pthread_mutex_lock(mutex_.get());
  assert(c == 0);
#endif
}

bool Mutex::TryLock() {
#ifdef CRU_WINDOWS
#else
  assert(mutex_);
  auto c = pthread_mutex_trylock(mutex_.get());
  assert(c == 0 || c == EBUSY);
  return c == 0 ? true : false;
#endif
}

void Mutex::Unlock() {
#ifdef CRU_WINDOWS
#else
  assert(mutex_);
  auto c = pthread_mutex_unlock(mutex_.get());
  assert(c == 0);
#endif
}

void Mutex::Destroy() {
#ifdef CRU_WINDOWS
#else
  if (mutex_ != nullptr) {
    auto c = pthread_mutex_destroy(mutex_.get());
    assert(c);
    mutex_ = nullptr;
  }
#endif
}

} // namespace cru
