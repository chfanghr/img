//
// Created by 方泓睿 on 12/11/20.
//

#ifndef IMG_INCLUDE_IMG_INTERNAL_ROUND_H_
#define IMG_INCLUDE_IMG_INTERNAL_ROUND_H_

#include "type_traits.h"
#include <cmath>

namespace img::internal {
template<typename Result, typename Value>
constexpr Result Floor(const Value &val) noexcept {
  const auto t = static_cast<Result>(val);
  if (val == static_cast<Value>(t))
    return t;

  return static_cast<Result>(t - val < 0 ? 1 : 0);
}

template<typename Result, typename Value>
constexpr Result Ceil(const Value &val) noexcept {
  const auto t = static_cast<Result>(val);
  if (val == static_cast<Value>(t))
    return t;

  return static_cast<Result>(t + val > 0 ? 1 : 0);
}

template<typename Result, typename Value>
inline Result RoundHalfUpDyn(const Value &val) noexcept {
  static_assert(kIsIntegral<Result>, "Result type should be integral");
  static_assert(kIsFloatingPoint<Value>, "Value type should be floating point");
  return static_cast<Result>(std::floor(ValueOf(val + Value{0.5})));
}

template<typename Result, typename Value>
constexpr Result RoundHalfUp(const Value &val) noexcept {
  static_assert(kIsIntegral<Result>, "Result type should be integral");
  static_assert(kIsFloatingPoint<Value>, "Value type should be floating point");
  return Floor<Result>(val + Value{0.5});
}

template<typename Result, typename Value>
Result RoundHalfDownDyn(const Value &val) noexcept {
  static_assert(kIsIntegral<Result>, "Result type should be integral");
  static_assert(kIsFloatingPoint<Value>, "Value type should be floating point");
  return static_cast<Result>(std::ceil(ValueOf(val - Value{0.5})));
}

template<typename Result, typename Value>
constexpr Result RoundHalfDown(const Value &val) noexcept {
  static_assert(kIsIntegral<Result>, "Result type should be integral");
  static_assert(kIsFloatingPoint<Value>, "Value type should be floating point");
  return Ceil<Result>(val - Value{0.5});
}

template<typename Result, typename Value>
inline Result RoundDyn(const Value &val) noexcept {
  static_assert(kIsIntegral<Result>, "Result type should be integral");
  static_assert(kIsFloatingPoint<Value>, "Value type should be floating point");
  return val >= 0 ? RoundHalfUpDyn<Result>(val) : RoundHalfDownDyn<Result>(val);
}

template<typename Result, typename Value>
constexpr Result Round(const Value &val) noexcept {
  return val >= 0 ? RoundHalfUp<Result>(val) : RoundHalfDown<Result>(val);
}

template<typename Result>
constexpr Result Round(char val) noexcept {
  static_assert(kIsIntegral<Result>, "Can only round to integral type");
  return static_cast<Result>(val);
}

template<typename Result>
constexpr Result Round(signed char val) noexcept {
  static_assert(kIsIntegral<Result>, "Can only round to integral type");
  return static_cast<Result>(val);
}

template<typename Result>
constexpr Result Round(unsigned char val) noexcept {
  static_assert(kIsIntegral<Result>, "Can only round to integral type");
  return static_cast<Result>(val);
}

template<typename Result>
constexpr Result Round(short val) noexcept {
  static_assert(kIsIntegral<Result>, "Can only round to integral type");
  return static_cast<Result>(val);
}

template<typename Result>
constexpr Result Round(unsigned short val) noexcept {
  static_assert(kIsIntegral<Result>, "Can only round to integral type");
  return static_cast<Result>(val);
}

template<typename Result>
constexpr Result Round(int val) noexcept {
  static_assert(kIsIntegral<Result>, "Can only round to integral type");
  return static_cast<Result>(val);
}

template<typename Result>
constexpr Result Round(unsigned int val) noexcept {
  static_assert(kIsIntegral<Result>, "Can only round to integral type");
  return static_cast<Result>(val);
}

template<typename Result>
constexpr Result Round(long val) noexcept {
  static_assert(kIsIntegral<Result>, "Can only round to integral type");
  return static_cast<Result>(val);
}

template<typename Result>
constexpr Result Round(unsigned long val) noexcept {
  static_assert(kIsIntegral<Result>, "Can only round to integral type");
  return static_cast<Result>(val);
}

template<typename Result>
constexpr Result Round(long long val) noexcept {
  static_assert(kIsIntegral<Result>, "Can only round to integral type");
  return static_cast<Result>(val);
}

template<typename Result>
constexpr Result Round(unsigned long long val) noexcept {
  static_assert(kIsIntegral<Result>, "Can only round to integral type");
  return static_cast<Result>(val);
}
}

#endif //IMG_INCLUDE_IMG_INTERNAL_ROUND_H_
