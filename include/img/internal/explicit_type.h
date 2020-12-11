//
// Created by 方泓睿 on 12/10/20.
//

#ifndef IMG_INCLUDE_IMG_INTERNAL_EXPLICIT_TYPE_H_
#define IMG_INCLUDE_IMG_INTERNAL_EXPLICIT_TYPE_H_

#include <type_traits>

namespace img::internal {
template<typename Value, typename Tag>
class ExplicitType {
 public:
  using ValueType = Value;
  using TagType = Tag;

  constexpr ExplicitType() noexcept = default;
  constexpr ExplicitType(const ExplicitType &) noexcept = default;
  constexpr ExplicitType &operator=(const ExplicitType &) noexcept = default;
  constexpr ExplicitType(ExplicitType &&) noexcept = default;
  constexpr ExplicitType &operator=(ExplicitType &&) noexcept = default;

  constexpr explicit ExplicitType(const Value &value) noexcept: value_(value) {}
  constexpr explicit ExplicitType(Value &&value) noexcept(std::is_nothrow_move_constructible_v<Value>):
      value_(value) {}

  constexpr explicit operator const Value &() const noexcept {
    return value_;
  }

  template<typename U, typename = std::enable_if<!std::is_same_v<Value, U>>>
  constexpr explicit operator U() const noexcept {
    return static_cast<U>(value_);
  }

  constexpr ExplicitType operator-() const noexcept {
    return ExplicitType{-value_};
  }

  constexpr ExplicitType &operator++() noexcept {
    value_++;
    return *this;
  }
  const ExplicitType operator++(int) const noexcept {  // NOLINT(readability-const-return-type)
    ExplicitType ret{*this};
    value_++;
    return ret;
  }
  constexpr ExplicitType &operator--() noexcept {
    value_--;
    return *this;
  }
  const ExplicitType operator--(int) const noexcept {  // NOLINT(readability-const-return-type)
    ExplicitType ret{*this};
    value_--;
    return ret;
  }

  constexpr Value &value() { return value_; }
  constexpr const Value &value() const { return value_; }

  friend constexpr void swap(ExplicitType &a, ExplicitType &b) {
    std::swap(a.value_, b.value_);
  }

 private:
  static_assert(std::is_arithmetic_v<Value>);

  Value value_;
};

template<typename Value>
constexpr auto ValueOf(const Value &value) noexcept { return value; }

template<typename V, typename T>
constexpr auto ValueOf(const ExplicitType<V, T> &val) noexcept { return val.value(); }

template<typename...Ts>
struct ExplicitTypeUniqueHelper;

template<typename ... Ts>
struct ExplicitTypeUnique {
  using Type = ExplicitTypeUniqueHelper<Ts...>;
};

template<typename ...Ts>
using ExplicitTypeUniqueType = typename ExplicitTypeUnique<Ts...>::Type;
}

#endif //IMG_INCLUDE_IMG_INTERNAL_EXPLICIT_TYPE_H_
