#pragma once

#include <exception>
#include <stdexcept>

#define CRU_UNUSED(entity) static_cast<void>(entity);

#define CRU__CONCAT(a, b) a##b
#define CRU_MAKE_UNICODE_LITERAL(str) CRU__CONCAT(u, #str)

#define CRU_DEFAULT_COPY(classname)                                            \
  classname(const classname &) = default;                                      \
  classname &operator=(const classname &) = default;

#define CRU_DEFAULT_MOVE(classname)                                            \
  classname(classname &&) = default;                                           \
  classname &operator=(classname &&) = default;

#define CRU_DELETE_COPY(classname)                                             \
  classname(const classname &) = delete;                                       \
  classname &operator=(const classname &) = delete;

#define CRU_DELETE_MOVE(classname)                                             \
  classname(classname &&) = delete;                                            \
  classname &operator=(classname &&) = delete;

class SerializationException : public std::runtime_error {
public:
  using runtime_error::runtime_error;
};
