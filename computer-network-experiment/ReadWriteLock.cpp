#include "ReadWriteLock.h"

#include <cassert>
#include <memory>

namespace cru {
ReadWriteLock::ReadWriteLock() {
#ifdef WIN32
  lock_ = std::make_unique<SRWLOCK>();
  InitializeSRWLock(lock_.get());
#else
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
  AcquireSRWLockShared(lock_.get());
}

void ReadWriteLock::WriteLock() {
  assert(lock_);
  AcquireSRWLockExclusive(lock_.get());
}

bool ReadWriteLock::ReadTryLock() {
  assert(lock_);
  return TryAcquireSRWLockShared(lock_.get()) != 0;
}

bool ReadWriteLock::WriteTryLock() {
  assert(lock_);
  return TryAcquireSRWLockExclusive(lock_.get()) != 0;
}

void ReadWriteLock::ReadUnlock() {
  assert(lock_);
  ReleaseSRWLockShared(lock_.get());
}

void ReadWriteLock::WriteUnlock() {
  assert(lock_);
  ReleaseSRWLockExclusive(lock_.get());
}

void ReadWriteLock::Destroy() {}
} // namespace cru