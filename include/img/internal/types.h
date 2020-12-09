//
// Created by 方泓睿 on 12/10/20.
//

#ifndef IMG_INCLUDE_IMG_INTERNAL_TYPES_H_
#define IMG_INCLUDE_IMG_INTERNAL_TYPES_H_

#include <cstdint>

namespace img::internal {
using float32_t = float;
using float64_t = double;

static_assert(sizeof(float32_t) == 32 / 8, "float32_t is not 32 bits");
static_assert(sizeof(float64_t) == 64 / 8, "float64_t is not 64 bits");

#if defined(IMG_DEFAULT_SCALAR_SIGNLE_PRECISION)
using default_float_t = float32_t
#else
using default_float_t = float64_t;
#endif

}

#endif //IMG_INCLUDE_IMG_INTERNAL_TYPES_H_
