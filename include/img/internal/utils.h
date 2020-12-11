//
// Created by 方泓睿 on 12/10/20.
//

#ifndef IMG_INCLUDE_IMG_INTERNAL_UTILS_H_
#define IMG_INCLUDE_IMG_INTERNAL_UTILS_H_

#include "promote.h"
#include "round.h"

#include <type_traits>
#include <cstdlib>
#include <array>

namespace img::internal {
template<typename T, std::size_t N>
constexpr std::array<T, N> MakeArray(T fill_value) {
  std::array<T, N> arr{{fill_value}};
  for (std::size_t i = 0; i < N; i++) {
    arr[i] = fill_value;
  }
  return arr;
}

template<typename T, std::size_t N, typename Func>
constexpr std::array<T, N> MakeArray(Func provider) {
  std::array<T, N> arr{};
  for (size_t i = 0; i < N; i++)
    arr[i] = provider(i);
  return arr;
}

template<typename T, typename U>
constexpr T Power(T base, U exponent) noexcept {
  static_assert(std::is_integral_v<U>, "Exponent type U should be integral");
  static_assert(std::is_unsigned_v<U>, "Exponent type U should be unsigned");
  return exponent == 0 ? T{1} : static_cast<T>(base * Power(base, U{exponent - 1}));
}

constexpr std::uint64_t NextPowerOfTwo(std::uint64_t x) {
  --x;
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  x |= x >> 32;
  return ++x;
}

template<typename Promoted, typename Coeff, Promoted shift>
constexpr Promoted RoundLinearCombinationCoeffFunc(std::size_t i) {
  using UnsignedPromotedType = std::make_unsigned_t<Promoted>;
  return RoundHalfUp<Promoted>(
      Coeff::kValues[i] * Promoted{Power(UnsignedPromotedType{2}, UnsignedPromotedType{shift})});
}

template<typename T, std::size_t N,
    typename Coeff,
    typename Promoted = Promote<T>,
    typename Array>
constexpr T ApproximateLinearCombination(const Array &src) noexcept {
  static_assert(kIsIntegral<T>, "Conversation type T should be integral");

  using PromotedType = Promoted;
  using UnsignedPromotedType = std::make_unsigned_t<PromotedType>;

  constexpr auto shift = UnsignedPromotedType{(sizeof(PromotedType) - sizeof(T)) * 8};
  constexpr auto half = PromotedType{Power(UnsignedPromotedType{2}, shift) / Promoted{2}};

  using Func = decltype(RoundLinearCombinationCoeffFunc<PromotedType, Coeff, shift>);

  constexpr auto c = MakeArray<PromotedType, N, Func>(RoundLinearCombinationCoeffFunc<PromotedType, Coeff, shift>);

  auto sum = PromotedType{0};
  for (std::size_t i = 0; i < N; i++)
    sum = PromotedType{sum + c[i] * src[i]};

  return static_cast<T>((sum + half) >> shift);
}

template<typename T, std::size_t N,
    typename Coeff,
    typename Array>
constexpr T LinearCombination(const Array &src) noexcept {
  static_assert(kIsIntegral<T>, "Conversation type T should be floating point");

  auto sum = T{0};
  for (std::size_t i = 0; i < N; i++)
    sum += static_cast<T>(Coeff::kValues[i]) * static_cast<T>(src[i]);

  return sum;
}
}
#endif //IMG_INCLUDE_IMG_INTERNAL_UTILS_H_
