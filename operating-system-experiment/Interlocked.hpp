#ifndef HRADER_INTERLOCKED_H
#define HRADER_INTERLOCKED_H

#include "Base.h"

namespace cru {
CRU_API void CruInterlockedAdd(volatile long long *v, long long a);
}

#endif
