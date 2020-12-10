//
// Created by 方泓睿 on 12/10/20.
//

#ifndef IMG_INCLUDE_IMG_INTERNAL_TYPES_H_
#define IMG_INCLUDE_IMG_INTERNAL_TYPES_H_

#include <cstdint>

namespace img {
namespace internal {
using Float32 = float;
using Float64 = double;

static_assert(sizeof(Float32) == 32 / 8, "Float32 is not 32 bits");
static_assert(sizeof(Float64) == 64 / 8, "Float64 is not 64 bits");

#if defined(IMG_DEFAULT_SCALAR_SIGNLE_PRECISION)
using DefaultFloat = Float32
#else
using DefaultFloat = Float64;
#endif
}

using internal::Float32;
using internal::Float64;
using internal::DefaultFloat;
}

#endif //IMG_INCLUDE_IMG_INTERNAL_TYPES_H_
