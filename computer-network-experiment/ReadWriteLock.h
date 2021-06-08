#pragma once
#include "Common.h"

#include <memory>

#ifdef WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif

namespace cru {
class ReadWriteLock {
  friend void swap(ReadWriteLock &left, ReadWriteLock &right);
public:
  ReadWriteLock();

  ReadWriteLock(ReadWriteLock &&other);
  ReadWriteLock &operator=(ReadWriteLock &&other);

  ~ReadWriteLock();

public:
  void ReadLock();
  void WriteLock();

  bool ReadTryLock();
  bool WriteTryLock();

  void ReadUnlock();
  void WriteUnlock();

private:
  void Destroy();

private:
#ifdef WIN32
  std::unique_ptr<SRWLOCK> lock_;
#else
  std::unique_ptr<pthread_rwlock_t> lock_;
#endif
};

void swap(ReadWriteLock &left, ReadWriteLock &right);
} // namespace cru
