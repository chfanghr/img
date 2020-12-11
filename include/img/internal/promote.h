//
// Created by 方泓睿 on 12/10/20.
//

#ifndef IMG_INCLUDE_IMG_INTERNAL_PROMOTE_H_
#define IMG_INCLUDE_IMG_INTERNAL_PROMOTE_H_

#include "../basic_types.h"

namespace img::internal {
template<typename T>
struct Promote;

template<>
struct Promote<std::uint8_t> {
  using Type = uint16_t;
};

template<>
struct Promote<std::uint16_t> {
  using Type = uint32_t;
};

template<>
struct Promote<std::uint32_t> {
  using Type = uint64_t;
};

template<>
struct Promote<std::uint64_t> {
  using Type = uint64_t;
};

template<>
struct Promote<std::int8_t> {
  using Type = int16_t;
};

template<>
struct Promote<std::int16_t> {
  using Type = int32_t;
};

template<>
struct Promote<std::int32_t> {
  using Type = int64_t;
};

template<>
struct Promote<std::int64_t> {
  using Type = int64_t;
};

template<>
struct Promote<Float32> {
  using Type = Float64;
};

template<>
struct Promote<Float64> {
  using Type = Float64;
};

template<typename T>
using PromotedType = typename Promote<T>::Type;
}

#endif //IMG_INCLUDE_IMG_INTERNAL_PROMOTE_H_
