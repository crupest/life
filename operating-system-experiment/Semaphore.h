#ifndef HEADER_SEMAPHORE_H
#define HEADER_SEMAPHORE_H

#include "Base.h"

#include <memory>

#ifdef CRU_WINDOWS
#include <Windows.h>
#else
#include <semaphore.h>
#endif

namespace cru {
class CRU_API Semaphore {
public:
  explicit Semaphore(unsigned init_value = 1);

  Semaphore(const Semaphore &other) = delete;
  Semaphore &operator=(const Semaphore &other) = delete;

  Semaphore(Semaphore &&other);
  Semaphore &operator=(Semaphore &&other);

  ~Semaphore();

public:
  void P();
  void V();

  void Acquire();
  bool TryAcquire();
  void Release();

private:
  void Destroy();

private:
#ifdef CRU_WINDOWS
  HANDLE handle_ = nullptr;
#else
  std::unique_ptr<sem_t> semaphore_;
#endif
};
} // namespace cru

#endif