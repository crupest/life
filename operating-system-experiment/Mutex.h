#ifndef HEADER_MUTEX_H
#define HEADER_MUTEX_H

#include "Base.h"

#include <memory>

#ifdef CRU_WINDOWS
#include <Windows.h>
#else
#include <pthread.h>
#endif

namespace cru {
class CRU_API Mutex {
public:
  Mutex();

  Mutex(const Mutex &other) = delete;
  Mutex &operator=(const Mutex &other) = delete;

  Mutex(Mutex &&other);
  Mutex &operator=(Mutex &&other);

  ~Mutex();

public:
  void Lock();
  bool TryLock();

  void Unlock();

private:
  void Destroy();

private:
#ifdef CRU_WINDOWS
  HANDLE handle_;
#else
  std::unique_ptr<pthread_mutex_t> mutex_;
#endif
};
} // namespace cru

#endif