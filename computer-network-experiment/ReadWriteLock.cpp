#include "ReadWriteLock.h"

#include <cassert>
#include <memory>
#include <pthread.h>

namespace cru {
ReadWriteLock::ReadWriteLock() {
#ifdef WIN32
  lock_ = std::make_unique<SRWLOCK>();
  InitializeSRWLock(lock_.get());
#else
  lock_.reset(new pthread_rwlock_t(PTHREAD_RWLOCK_INITIALIZER));
  pthread_rwlock_init(lock_.get(), nullptr);
#endif
}

ReadWriteLock::ReadWriteLock(ReadWriteLock &&other)
    : lock_(std::move(other.lock_)) {}

ReadWriteLock &ReadWriteLock::operator=(ReadWriteLock &&other) {
  if (this != &other) {
    Destroy();
    lock_ = std::move(other.lock_);
  }
  return *this;
}

ReadWriteLock::~ReadWriteLock() { Destroy(); }

void ReadWriteLock::ReadLock() {
  assert(lock_);
#ifdef WIN32
  AcquireSRWLockShared(lock_.get());
#else
  pthread_rwlock_rdlock(lock_.get());
#endif
}

void ReadWriteLock::WriteLock() {
  assert(lock_);
#ifdef WIN32
  AcquireSRWLockExclusive(lock_.get());
#else
  pthread_rwlock_wrlock(lock_.get());
#endif
}

bool ReadWriteLock::ReadTryLock() {
  assert(lock_);
#ifdef WIN32
  return TryAcquireSRWLockShared(lock_.get()) != 0;
#else
  return pthread_rwlock_tryrdlock(lock_.get()) == 0;
#endif
}

bool ReadWriteLock::WriteTryLock() {
  assert(lock_);
#ifdef WIN32
  return TryAcquireSRWLockExclusive(lock_.get()) != 0;
#else
  return pthread_rwlock_trywrlock(lock_.get()) == 0;
#endif
}

void ReadWriteLock::ReadUnlock() {
  assert(lock_);
#ifdef WIN32
  ReleaseSRWLockShared(lock_.get());
#else
  pthread_rwlock_unlock(lock_.get());
#endif
}

void ReadWriteLock::WriteUnlock() {
  assert(lock_);
#ifdef WIN32
  ReleaseSRWLockExclusive(lock_.get());
#else
  pthread_rwlock_unlock(lock_.get());
#endif
}

void ReadWriteLock::Destroy() {
#ifndef WIN32
  if (lock_ != nullptr)
    pthread_rwlock_destroy(lock_.get());
#endif
}

void swap(ReadWriteLock &left, ReadWriteLock &right) {
  auto temp = std::move(left.lock_);
  left.lock_ = std::move(right.lock_);
  right.lock_ = std::move(temp);
}

} // namespace cru