#include "Interlocked.hpp"

#ifdef CRU_WINDOWS
#include <Windows.h>
#else
#endif

namespace cru {
void CruInterlockedAdd(volatile long long *v, long long a) {
#ifdef CRU_WINDOWS
  InterlockedAdd64(v, a);
#else
  __sync_fetch_and_add(v, a);
#endif
}
} // namespace cru
