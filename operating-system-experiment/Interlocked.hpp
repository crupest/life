#ifndef HRADER_INTERLOCKED_H
#define HRADER_INTERLOCKED_H

#include "Base.h"

namespace cru {
CRU_API void InterlockedAdd(volatile long long *v, long long a);
}

#endif
