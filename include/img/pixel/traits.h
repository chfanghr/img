//
// Created by 方泓睿 on 12/10/20.
//

#ifndef IMG_INCLUDE_IMG_PIXEL_TRAITS_H_
#define IMG_INCLUDE_IMG_PIXEL_TRAITS_H_

#include "format.h"
#include "pixel.h"
#include "../internal/utils.h"

#include <cstdint>
#include <cstdlib>

namespace img::pixel {
template<typename Element>
struct Traits {
  using ElementType = Element;

  static constexpr int16_t kNrChannels = 1;
  static constexpr std::size_t kNrBytes = sizeof(ElementType);
  static constexpr std::size_t kNrBytesPerChannel = sizeof(ElementType);

  static constexpr bool kIsIntegral = std::is_integral_v<ElementType>;
  static constexpr bool kIsFloatingPoint = std::is_floating_point_v<ElementType>;
  static constexpr bool kIsUnsigned = std::is_unsigned_v<ElementType>;

  static constexpr Format kFormat = Format::kUnknown;

  static constexpr SampleFormat kSampleFormat = kIsIntegral ?
                                                (kIsUnsigned ?
                                                 SampleFormat::kUnsignedInteger :
                                                 SampleFormat::kSignedInteger) :
                                                (kIsFloatingPoint ?
                                                 SampleFormat::kFloatingPoint :
                                                 SampleFormat::kUnknown);

  static constexpr ElementType kZeroElement = ElementType{0};
};

template<typename T, std::size_t nr_channels_, Format format_>
struct Traits<Pixel<T, nr_channels_, format_>> {
  using PixelType = Pixel<T, nr_channels_, format_>;
  using ElementType = T;

  static constexpr int16_t kNrChannels = static_cast<int16_t>(nr_channels_);
  static constexpr std::size_t kNrBytes = sizeof(PixelType);
  static constexpr std::size_t kNrBytesPerChannel = sizeof(ElementType);\

  static constexpr bool kIsIntegral = std::is_integral_v<ElementType>;
  static constexpr bool kIsFloatingPoint = std::is_floating_point_v<ElementType>;
  static constexpr bool kIsUnsigned = std::is_unsigned_v<ElementType>;

  static constexpr Format kFormat = format_;

  static constexpr SampleFormat kSampleFormat = kIsIntegral ?
                                                (kIsUnsigned ?
                                                 SampleFormat::kUnsignedInteger :
                                                 SampleFormat::kSignedInteger) :
                                                (kIsFloatingPoint ?
                                                 SampleFormat::kFloatingPoint :
                                                 SampleFormat::kUnknown);

  static constexpr PixelType kZeroElement = PixelType{internal::MakeArray<T, nr_channels_>(0)};
};

template<typename T, std::size_t nr_channels_, Format format_>
struct Traits<const Pixel<T, nr_channels_, format_>> {
  using PixelType = Pixel<T, nr_channels_, format_>;
  using ElementType = T;

  static constexpr int16_t kNrChannels = static_cast<int16_t>(nr_channels_);
  static constexpr std::size_t kNrBytes = sizeof(PixelType);
  static constexpr std::size_t kNrBytesPerChannel = sizeof(ElementType);\

  static constexpr bool kIsIntegral = std::is_integral_v<ElementType>;
  static constexpr bool kIsFloatingPoint = std::is_floating_point_v<ElementType>;
  static constexpr bool kIsUnsigned = std::is_unsigned_v<ElementType>;

  static constexpr Format kFormat = format_;

  static constexpr SampleFormat kSampleFormat = kIsIntegral ?
                                                (kIsUnsigned ?
                                                 SampleFormat::kUnsignedInteger :
                                                 SampleFormat::kSignedInteger) :
                                                (kIsFloatingPoint ?
                                                 SampleFormat::kFloatingPoint :
                                                 SampleFormat::kUnknown);

  static constexpr PixelType kZeroElement = PixelType{internal::MakeArray<T, nr_channels_>(0)};
};
}

#endif //IMG_INCLUDE_IMG_PIXEL_TRAITS_H_
