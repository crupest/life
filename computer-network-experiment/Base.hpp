#pragma once
#include "PreConfig.hpp"

#include <exception>
#include <stdexcept>
#include <gsl/gsl>

#define CRU_UNUSED(entity) static_cast<void>(entity);

#define CRU__CONCAT(a, b) a##b
#define CRU_MAKE_UNICODE_LITERAL(str) CRU__CONCAT(u, #str)

#define CRU_DEFAULT_COPY(classname)      \
  classname(const classname&) = default; \
  classname& operator=(const classname&) = default;

#define CRU_DEFAULT_MOVE(classname) \
  classname(classname&&) = default; \
  classname& operator=(classname&&) = default;

#define CRU_DELETE_COPY(classname)      \
  classname(const classname&) = delete; \
  classname& operator=(const classname&) = delete;

#define CRU_DELETE_MOVE(classname) \
  classname(classname&&) = delete; \
  classname& operator=(classname&&) = delete;

namespace cru {
class Object {
 public:
  Object() = default;
  CRU_DEFAULT_COPY(Object)
  CRU_DEFAULT_MOVE(Object)
  virtual ~Object() = default;
};

struct Interface {
  Interface() = default;
  CRU_DELETE_COPY(Interface)
  CRU_DELETE_MOVE(Interface)
  virtual ~Interface() = default;
};

[[noreturn]] inline void UnreachableCode() { std::terminate(); }

using Index = gsl::index;

// https://www.boost.org/doc/libs/1_54_0/doc/html/hash/reference.html#boost.hash_combine
template <class T>
inline void hash_combine(std::size_t& s, const T& v) {
  std::hash<T> h;
  s ^= h(v) + 0x9e3779b9 + (s << 6) + (s >> 2);
}

#define CRU_DEFINE_CLASS_LOG_TAG(tag) \
 private:                             \
  constexpr static std::u16string_view log_tag = tag;
}  // namespace cru
