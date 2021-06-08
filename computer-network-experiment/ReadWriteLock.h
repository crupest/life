#pragma once
#include "Common.h"

#include <memory>

#ifdef WIN32
#include <Windows.h>
#else
#endif

namespace cru {
class ReadWriteLock {
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
#endif
};
} // namespace cru
