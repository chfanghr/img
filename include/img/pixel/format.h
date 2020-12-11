//
// Created by 方泓睿 on 12/9/20.
//

#ifndef IMG_INCLUDE_IMG_PIXEL_FORMAT_H_
#define IMG_INCLUDE_IMG_PIXEL_FORMAT_H_

#include <cstdlib>

namespace img::pixel {
enum class Format : unsigned char {
  kY,
  kX,

  kYA,
  kXX,

  kRGB,
  kBGR,
  kYCbCr,
  XXX,

  kRGBA,
  kBGRA,
  kARGB,
  kABGR,
  kCMYK,
  kYCCK,
  kXXXX,

  kUnknown,
  kInvalid
};

constexpr std::size_t GetNrChannels(Format format) noexcept {
  switch (format) {
    case Format::kY:
    case Format::kX:return 1;

    case Format::kYA:
    case Format::kXX:return 2;

    case Format::kRGB:
    case Format::kBGR:
    case Format::kYCbCr:
    case Format::XXX:return 3;

    case Format::kRGBA:
    case Format::kBGRA:
    case Format::kARGB:
    case Format::kABGR:
    case Format::kCMYK:
    case Format::kYCCK:
    case Format::kXXXX:return 4;

    case Format::kUnknown:
    case Format::kInvalid:return 0;
  }

  return 0;
}

template<Format format>
constexpr std::size_t GetNrChannels() noexcept {
  return GetNrChannels(format);
}

constexpr bool HasAlphaChannel(Format format) noexcept {
  switch (format) {
    case Format::kY:
    case Format::kX:
    case Format::kXX:
    case Format::kRGB:
    case Format::kBGR:
    case Format::kYCbCr:
    case Format::XXX:
    case Format::kCMYK:
    case Format::kYCCK:
    case Format::kXXXX:
    case Format::kUnknown:
    case Format::kInvalid:return false;

    case Format::kYA:
    case Format::kRGBA:
    case Format::kBGRA:
    case Format::kARGB:
    case Format::kABGR:return true;
  }

  return false;
}

template<Format format>
constexpr bool HasAlphaChannel() noexcept {
  return HasAlphaChannel(format);
}

constexpr bool ConversationRequireAlphaValue(Format src, Format dst) noexcept {
  return !HasAlphaChannel(src) && HasAlphaChannel(dst);
}

template<Format src, Format dst>
constexpr bool ConversationRequireAlphaValue() noexcept {
  return ConversationRequireAlphaValue(src, dst);
}

enum class SampleFormat : unsigned char {
  kUnsignedInteger,
  kSignedInteger,
  kFloatingPoint,
  kUnknown
};
}

#endif //IMG_INCLUDE_IMG_PIXEL_FORMAT_H_
