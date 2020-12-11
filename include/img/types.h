//
// Created by 方泓睿 on 12/12/20.
//

#ifndef IMG_INCLUDE_IMG_TYPES_H_
#define IMG_INCLUDE_IMG_TYPES_H_

#include "internal/promote.h"
#include "basic_types.h"

#include "pixel/pixel.h"

namespace img {
using internal::Promote;
using internal::PromotedType;

using pixel::Pixel;
using PixelFormat = pixel::Format;
}
#endif //IMG_INCLUDE_IMG_TYPES_H_
