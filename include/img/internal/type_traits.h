//
// Created by 方泓睿 on 2020/12/11.
//

#ifndef IMG_INCLUDE_IMG_INTERNAL_TYPE_TRAITS_H_
#define IMG_INCLUDE_IMG_INTERNAL_TYPE_TRAITS_H_

#include "explicit_type.h"
#include <type_traits>

namespace img::internal {
template<typename T>
struct IsIntegral : std::integral_constant<bool, std::is_integral_v<T>> {};

template<typename Value, typename Tag>
struct IsIntegral<ExplicitType < Value, Tag>> : std::integral_constant<bool, std::is_integral_v<Value>> {
};

template<typename T>
constexpr bool kIsIntegral = IsIntegral<T>::value;

template<typename T>
struct IsFloatingPoint : std::integral_constant<bool, std::is_floating_point_v<T>> {};

template<typename Value, typename Tag>
struct IsFloatingPoint<ExplicitType < Value, Tag>>: std::integral_constant<bool, std::is_integral_v<Value>>{
};

template<typename T>
constexpr bool kIsFloatingPoint = IsFloatingPoint<T>::value;
}
#endif //IMG_INCLUDE_IMG_INTERNAL_TYPE_TRAITS_H_
