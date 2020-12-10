//
// Created by 方泓睿 on 12/10/20.
//

#ifndef IMG_INCLUDE_IMG_INTERNAL_UTILS_H_
#define IMG_INCLUDE_IMG_INTERNAL_UTILS_H_

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
}
#endif //IMG_INCLUDE_IMG_INTERNAL_UTILS_H_
