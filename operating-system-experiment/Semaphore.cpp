#include "Semaphore.h"

#include <cassert>

#ifndef CRU_WINDOWS
#include <errno.h>
#endif

namespace cru {
Semaphore::Semaphore(unsigned init_value) {
#ifdef CRU_WINDOWS
#else
  semaphore_ = std::make_unique<sem_t>();
  auto c = sem_init(semaphore_.get(), 0, init_value);
  assert(c == 0);
#endif
}

Semaphore::Semaphore(Semaphore &&other)
#ifdef CRU_WINDOWS
#else
    : semaphore_(std::move(other.semaphore_))
#endif
{
}

Semaphore &Semaphore::operator=(Semaphore &&other) {
  if (this != &other) {
    Destroy();
#ifdef CRU_WINDOWS
#else
    semaphore_ = std::move(other.semaphore_);
#endif
  }
  return *this;
}

Semaphore::~Semaphore() { Destroy(); }

void Semaphore::P() { Acquire(); }
void Semaphore::V() { Release(); }

void Semaphore::Acquire() {
#ifdef CRU_WINDOWS
#else
  auto c = sem_wait(semaphore_.get());
  assert(c == 0);
#endif
}

bool Semaphore::TryAcquire() {
#ifdef CRU_WINDOWS
#else
  auto c = sem_trywait(semaphore_.get());
  assert((c == 0) || (c == -1 && errno == EAGAIN));
  return c == 0 ? true : false;
#endif
}

void Semaphore::Release() {
#ifdef CRU_WINDOWS
#else
  auto c = sem_post(semaphore_.get());
  assert(c == 0);
#endif
}

void Semaphore::Destroy() {
#ifdef CRU_WINDOWS
#else
  if (semaphore_ != nullptr) {
    auto c = sem_destroy(semaphore_.get());
    assert(c == 0);
    semaphore_ = nullptr;
  }
#endif
}
} // namespace cru