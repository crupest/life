#include "StringUtil.hpp"
#include "Base.hpp"

namespace cru {
namespace {
template <typename UInt, int number_of_bit, typename ReturnType>
inline std::enable_if_t<std::is_unsigned_v<UInt>, ReturnType>
ExtractBits(UInt n) {
  return static_cast<ReturnType>(n & ((1u << number_of_bit) - 1));
}
} // namespace

CodePoint Utf8NextCodePoint(std::string_view str, Index current,
                            Index *next_position) {
  CodePoint result;

  if (current >= static_cast<Index>(str.length())) {
    result = k_invalid_code_point;
  } else {
    const auto cu0 = static_cast<std::uint8_t>(str[current++]);

    auto read_next_folowing_code = [&str, &current]() -> CodePoint {
      if (current == static_cast<Index>(str.length()))
        throw TextEncodeException(
            "Unexpected end when read continuing byte of multi-byte code "
            "point.");

      const auto u = static_cast<std::uint8_t>(str[current]);
      if (!(u & (1u << 7)) || (u & (1u << 6))) {
        throw TextEncodeException(
            "Unexpected bad-format (not 0b10xxxxxx) continuing byte of "
            "multi-byte code point.");
      }

      return ExtractBits<std::uint8_t, 6, CodePoint>(str[current++]);
    };

    if ((1u << 7) & cu0) {
      if ((1u << 6) & cu0) {     // 2~4-length code point
        if ((1u << 5) & cu0) {   // 3~4-length code point
          if ((1u << 4) & cu0) { // 4-length code point
            if (cu0 & (1u << 3)) {
              throw TextEncodeException(
                  "Unexpected bad-format begin byte (not 0b11110xxx) of 4-byte"
                  "code point.");
            }

            const CodePoint s0 = ExtractBits<std::uint8_t, 3, CodePoint>(cu0)
                                 << (6 * 3);
            const CodePoint s1 = read_next_folowing_code() << (6 * 2);
            const CodePoint s2 = read_next_folowing_code() << 6;
            const CodePoint s3 = read_next_folowing_code();
            result = s0 + s1 + s2 + s3;
          } else { // 3-length code point
            const CodePoint s0 = ExtractBits<std::uint8_t, 4, CodePoint>(cu0)
                                 << (6 * 2);
            const CodePoint s1 = read_next_folowing_code() << 6;
            const CodePoint s2 = read_next_folowing_code();
            result = s0 + s1 + s2;
          }
        } else { // 2-length code point
          const CodePoint s0 = ExtractBits<std::uint8_t, 5, CodePoint>(cu0)
                               << 6;
          const CodePoint s1 = read_next_folowing_code();
          result = s0 + s1;
        }
      } else {
        throw TextEncodeException(
            "Unexpected bad-format (0b10xxxxxx) begin byte of a code point.");
      }
    } else {
      result = static_cast<CodePoint>(cu0);
    }
  }

  if (next_position != nullptr)
    *next_position = current;
  return result;
}

CodePoint Utf16NextCodePoint(std::u16string_view str, Index current,
                             Index *next_position) {
  CodePoint result;

  if (current >= static_cast<Index>(str.length())) {
    result = k_invalid_code_point;
  } else {
    const auto cu0 = str[current++];

    if (!IsUtf16SurrogatePairCodeUnit(cu0)) { // 1-length code point
      result = static_cast<CodePoint>(cu0);
    } else if (IsUtf16SurrogatePairLeading(cu0)) { // 2-length code point
      if (current >= static_cast<Index>(str.length())) {
        throw TextEncodeException(
            "Unexpected end when reading second code unit of surrogate pair.");
      }
      const auto cu1 = str[current++];

      if (!IsUtf16SurrogatePairTrailing(cu1)) {
        throw TextEncodeException(
            "Unexpected bad-range second code unit of surrogate pair.");
      }

      const auto s0 = ExtractBits<std::uint16_t, 10, CodePoint>(cu0) << 10;
      const auto s1 = ExtractBits<std::uint16_t, 10, CodePoint>(cu1);

      result = s0 + s1 + 0x10000;

    } else {
      throw TextEncodeException(
          "Unexpected bad-range first code unit of surrogate pair.");
    }
  }

  if (next_position != nullptr)
    *next_position = current;
  return result;
}

CodePoint Utf16PreviousCodePoint(std::u16string_view str, Index current,
                                 Index *previous_position) {
  CodePoint result;
  if (current <= 0) {
    result = k_invalid_code_point;
  } else {
    const auto cu0 = str[--current];

    if (!IsUtf16SurrogatePairCodeUnit(cu0)) { // 1-length code point
      result = static_cast<CodePoint>(cu0);
    } else if (IsUtf16SurrogatePairTrailing(cu0)) { // 2-length code point
      if (current <= 0) {
        throw TextEncodeException(
            "Unexpected end when reading first code unit of surrogate pair.");
      }
      const auto cu1 = str[--current];

      if (!IsUtf16SurrogatePairLeading(cu1)) {
        throw TextEncodeException(
            "Unexpected bad-range first code unit of surrogate pair.");
      }

      const auto s0 = ExtractBits<std::uint16_t, 10, CodePoint>(cu1) << 10;
      const auto s1 = ExtractBits<std::uint16_t, 10, CodePoint>(cu0);

      result = s0 + s1 + 0x10000;

    } else {
      throw TextEncodeException(
          "Unexpected bad-range second code unit of surrogate pair.");
    }
  }

  if (previous_position != nullptr)
    *previous_position = current;
  return result;
}

void Utf8EncodeCodePointAppend(CodePoint code_point, std::string &str) {
  auto write_continue_byte = [&str](std::uint8_t byte6) {
    str.push_back((1u << 7) + (((1u << 6) - 1) & byte6));
  };

  if (code_point >= 0 && code_point <= 0x007F) {
    str.push_back(static_cast<char>(code_point));
  } else if (code_point >= 0x0080 && code_point <= 0x07FF) {
    std::uint32_t unsigned_code_point = code_point;
    str.push_back(static_cast<char>(ExtractBits<std::uint32_t, 5, std::uint8_t>(
                                        (unsigned_code_point >> 6)) +
                                    0b11000000));
    write_continue_byte(
        ExtractBits<std::uint32_t, 6, std::uint8_t>(unsigned_code_point));
  } else if (code_point >= 0x0800 && code_point <= 0xFFFF) {
    std::uint32_t unsigned_code_point = code_point;
    str.push_back(static_cast<char>(ExtractBits<std::uint32_t, 4, std::uint8_t>(
                                        (unsigned_code_point >> (6 * 2))) +
                                    0b11100000));
    write_continue_byte(
        ExtractBits<std::uint32_t, 6, std::uint8_t>(unsigned_code_point >> 6));
    write_continue_byte(
        ExtractBits<std::uint32_t, 6, std::uint8_t>(unsigned_code_point));
  } else if (code_point >= 0x10000 && code_point <= 0x10FFFF) {
    std::uint32_t unsigned_code_point = code_point;
    str.push_back(static_cast<char>(ExtractBits<std::uint32_t, 3, std::uint8_t>(
                                        (unsigned_code_point >> (6 * 3))) +
                                    0b11110000));
    write_continue_byte(ExtractBits<std::uint32_t, 6, std::uint8_t>(
        unsigned_code_point >> (6 * 2)));
    write_continue_byte(
        ExtractBits<std::uint32_t, 6, std::uint8_t>(unsigned_code_point >> 6));
    write_continue_byte(
        ExtractBits<std::uint32_t, 6, std::uint8_t>(unsigned_code_point));
  } else {
    throw TextEncodeException("Code point out of range.");
  }
}

void Utf16EncodeCodePointAppend(CodePoint code_point, std::u16string &str) {
  if ((code_point >= 0 && code_point <= 0xD7FF) ||
      (code_point >= 0xE000 && code_point <= 0xFFFF)) {
    str.push_back(static_cast<char16_t>(code_point));
  } else if (code_point >= 0x10000 && code_point <= 0x10FFFF) {
    std::uint32_t u = code_point - 0x10000;
    str.push_back(static_cast<char16_t>(
        ExtractBits<std::uint32_t, 10, std::uint32_t>(u >> 10) + 0xD800u));
    str.push_back(static_cast<char16_t>(
        ExtractBits<std::uint32_t, 10, std::uint32_t>(u) + 0xDC00u));
  } else {
    throw TextEncodeException("Code point out of range.");
  }
}

std::string ToUtf8(std::u16string_view s) {
  std::string result;
  for (CodePoint cp : Utf16CodePointIterator{s}) {
    Utf8EncodeCodePointAppend(cp, result);
  }
  return result;
}

std::u16string ToUtf16(std::string_view s) {
  std::u16string result;
  for (CodePoint cp : Utf8CodePointIterator{s}) {
    Utf16EncodeCodePointAppend(cp, result);
  }
  return result;
}

bool Utf16IsValidInsertPosition(std::u16string_view s, gsl::index position) {
  if (position < 0)
    return false;
  if (position > static_cast<gsl::index>(s.size()))
    return false;
  if (position == 0)
    return true;
  if (position == static_cast<gsl::index>(s.size()))
    return true;
  return !IsUtf16SurrogatePairTrailing(s[position]);
}

gsl::index Utf16BackwardUntil(std::u16string_view str, gsl::index position,
                              const std::function<bool(CodePoint)> &predicate) {
  if (position <= 0)
    return position;
  while (true) {
    gsl::index p = position;
    auto c = Utf16PreviousCodePoint(str, p, &position);
    if (predicate(c))
      return p;
    if (c == k_invalid_code_point)
      return p;
  }
  UnreachableCode();
}

gsl::index Utf16ForwardUntil(std::u16string_view str, gsl::index position,
                             const std::function<bool(CodePoint)> &predicate) {
  if (position >= static_cast<gsl::index>(str.size()))
    return position;
  while (true) {
    gsl::index p = position;
    auto c = Utf16NextCodePoint(str, p, &position);
    if (predicate(c))
      return p;
    if (c == k_invalid_code_point)
      return p;
  }
  UnreachableCode();
}

inline bool IsSpace(CodePoint c) { return c == 0x20 || c == 0xA; }

gsl::index Utf16PreviousWord(std::u16string_view str, gsl::index position,
                             bool *is_space) {
  if (position <= 0)
    return position;
  auto c = Utf16PreviousCodePoint(str, position, nullptr);
  if (IsSpace(c)) { // TODO: Currently only test against 0x20(space).
    if (is_space)
      *is_space = true;
    return Utf16BackwardUntil(str, position,
                              [](CodePoint c) { return !IsSpace(c); });
  } else {
    if (is_space)
      *is_space = false;
    return Utf16BackwardUntil(str, position, IsSpace);
  }
}

gsl::index Utf16NextWord(std::u16string_view str, gsl::index position,
                         bool *is_space) {
  if (position >= static_cast<gsl::index>(str.size()))
    return position;
  auto c = Utf16NextCodePoint(str, position, nullptr);
  if (IsSpace(c)) { // TODO: Currently only test against 0x20(space).
    if (is_space)
      *is_space = true;
    return Utf16ForwardUntil(str, position,
                             [](CodePoint c) { return !IsSpace(c); });
  } else {
    if (is_space)
      *is_space = false;
    return Utf16ForwardUntil(str, position, IsSpace);
  }
}
} // namespace cru
