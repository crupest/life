#include "Semaphore.h"

#include <cassert>

#ifndef CRU_WINDOWS
#include <errno.h>
#endif

namespace cru {
Semaphore::Semaphore(unsigned init_value) {
#ifdef CRU_WINDOWS
  handle_ = CreateSemaphoreW(nullptr, init_value, 100, nullptr);
  assert(handle_);
#else
  semaphore_ = std::make_unique<sem_t>();
  auto c = sem_init(semaphore_.get(), 0, init_value);
  assert(c == 0);
#endif
}

Semaphore::Semaphore(Semaphore &&other)
#ifdef CRU_WINDOWS
    : handle_(other.handle_)
#else
    : semaphore_(std::move(other.semaphore_))
#endif
{
#ifdef CRU_WINDOWS
  other.handle_ = nullptr;
#endif
}

Semaphore &Semaphore::operator=(Semaphore &&other) {
  if (this != &other) {
    Destroy();
#ifdef CRU_WINDOWS
    handle_ = other.handle_;
    other.handle_ = nullptr;
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
  auto c = WaitForSingleObject(handle_, INFINITE);
  assert(c == WAIT_OBJECT_0);
#else
  auto c = sem_wait(semaphore_.get());
  assert(c == 0);
#endif
}

bool Semaphore::TryAcquire() {
#ifdef CRU_WINDOWS
  auto c = WaitForSingleObject(handle_, 0);
  assert(c == WAIT_OBJECT_0 || c == WAIT_TIMEOUT);
  return c == WAIT_OBJECT_0 ? true : false;
#else
  auto c = sem_trywait(semaphore_.get());
  assert((c == 0) || (c == -1 && errno == EAGAIN));
  return c == 0 ? true : false;
#endif
}

void Semaphore::Release() {
#ifdef CRU_WINDOWS
  auto c = ReleaseSemaphore(handle_, 1, nullptr);
  assert(c);
#else
  auto c = sem_post(semaphore_.get());
  assert(c == 0);
#endif
}

void Semaphore::Destroy() {
#ifdef CRU_WINDOWS
  if (handle_ != nullptr) {
    auto c = CloseHandle(handle_);
    assert(c);
    handle_ = nullptr;
  }
#else
  if (semaphore_ != nullptr) {
    auto c = sem_destroy(semaphore_.get());
    assert(c == 0);
    semaphore_ = nullptr;
  }
#endif
}
} // namespace cru