#include "Interlocked.hpp"

#ifdef CRU_WINDOWS
#include <Windows.h>
#else
#endif

namespace cru {
void InterlockedIncrease(volatile long long *v) {
#ifdef CRU_WINDOWS
  InterlockedIncrement64(v);
#else

#endif
}
} // namespace cru
