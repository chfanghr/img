//
// Created by 方泓睿 on 12/10/20.
//

#ifndef IMG_INCLUDE_IMG_PIXEL_CONVERSATIONS_H_
#define IMG_INCLUDE_IMG_PIXEL_CONVERSATIONS_H_

#include "../internal/utils.h"
#include "traits.h"

namespace img::pixel {
template<
    Format format_src, Format format_dst,
    typename PixelSrc,
    typename = std::enable_if_t<Traits<PixelSrc>::kFormat == Format::kUnknown>,
    typename = std::enable_if_t<!ConversationRequireAlphaValue<format_src, format_dst>()>
>
constexpr auto Convert(const PixelSrc &src) noexcept;

template<
    Format format_src, Format format_dst,
    typename PixelSrc, typename Element,
    typename = std::enable_if_t<Traits<PixelSrc>::kFormat == Format::kUnknown>,
    typename = std::enable_if_t<ConversationRequireAlphaValue<format_src, format_dst>()>
>
constexpr auto Convert(const PixelSrc &src, const Element &alpha) noexcept;

template<
    Format format_dst,
    typename PixelSrc,
    typename = std::enable_if_t<Traits<PixelSrc>::kFormat != Format::kUnknown>,
    typename = std::enable_if_t<!ConversationRequireAlphaValue<Traits<PixelSrc>::kFormat, format_dst>()>
>
constexpr auto Convert(const PixelSrc &src) noexcept;

template<
    Format format_dst,
    typename PixelSrc, typename Element,
    typename = std::enable_if_t<Traits<PixelSrc>::kFormat != Format::kUnknown>,
    typename = std::enable_if_t<ConversationRequireAlphaValue<Traits<PixelSrc>::kFormat, format_dst>()>
>
constexpr auto Convert(const PixelSrc &src, const Element &alpha) noexcept;

template<typename T, std::size_t N>
constexpr Pixel<T, N> YToNChannel(const Pixel<T, 1> &src) noexcept;

namespace impl {
// Ref: mathworks.com/help/matlab/ref/rgb2gray.html
struct RGBToYCoefficients {
  static constexpr std::array<DefaultFloat, 3> kValues{
      DefaultFloat(0.299),
      DefaultFloat(0.587),
      DefaultFloat(0.144),
  };
};

struct BGRToYCoefficients {
  static constexpr std::array<DefaultFloat, 3> kValues{
      DefaultFloat(0.144),
      DefaultFloat(0.587),
      DefaultFloat(0.299),
  };
};

template<Format src_format, Format dst_format>
struct PixelConversation;

// kY -> ?

template<>
struct PixelConversation<Format::kY, Format::kY> {
  template<typename T, Format format>
  static constexpr Pixel<T, 1, Format::kY> Apply(const Pixel<T, 1, format> &src) noexcept {
    return src;
  }
};

template<>
struct PixelConversation<Format::kY, Format::kYA> {
  template<typename T, Format format>
  static constexpr Pixel<T, 2, Format::kYA> Apply(const Pixel<T, 1, format> &src, const T &alpha) noexcept {
    return {src[0], alpha};
  }
};

template<>
struct PixelConversation<Format::kY, Format::kRGB> {
  template<typename T, Format format>
  static constexpr Pixel<T, 3, Format::kRGB> Apply(const Pixel<T, 1, format> &src) noexcept {
    return {src[0], src[0], src[0]};
  }
};

template<>
struct PixelConversation<Format::kY, Format::kGBR> {
  template<typename T, Format format>
  static constexpr Pixel<T, 3, Format::kGBR> Apply(const Pixel<T, 1, format> &src) noexcept {
    return {src[0], src[0], src[0]};
  }
};

template<>
struct PixelConversation<Format::kY, Format::kRGBA> {
  template<typename T, Format format>
  static constexpr Pixel<T, 4, Format::kRGBA> Apply(const Pixel<T, 1, format> &src, const T &alpha) noexcept {
    return {src[0], src[0], src[0], alpha};
  }
};

template<>
struct PixelConversation<Format::kY, Format::kBGRA> {
  template<typename T, Format format>
  static constexpr Pixel<T, 4, Format::kBGRA> Apply(const Pixel<T, 1, format> &src, const T &alpha) noexcept {
    return {src[0], src[0], src[0], alpha};
  }
};

template<>
struct PixelConversation<Format::kY, Format::kABGR> {
  template<typename T, Format format>
  static constexpr Pixel<T, 4, Format::kABGR> Apply(const Pixel<T, 1, format> &src, const T &alpha) noexcept {
    return {alpha, src[0], src[0], src[0]};
  }
};

template<>
struct PixelConversation<Format::kY, Format::kARGB> {
  template<typename T, Format format>
  static constexpr Pixel<T, 4, Format::kARGB> Apply(const Pixel<T, 1, format> &src, const T &alpha) noexcept {
    return {alpha, src[0], src[0], src[0]};
  }
};

// kYA -> ?

template<>
struct PixelConversation<Format::kYA, Format::kYA> {
  template<typename T, Format format>
  static constexpr Pixel<T, 2, Format::kYA> Apply(const Pixel<T, 2, format> &src) noexcept {
    return src;
  }
};

template<>
struct PixelConversation<Format::kYA, Format::kY> {
  template<typename T, Format format>
  static constexpr Pixel<T, 1, Format::kY> Apply(const Pixel<T, 2, format> &src) noexcept {
    return {src[0]};
  }
};

template<>
struct PixelConversation<Format::kYA, Format::kRGB> {
  template<typename T, Format format>
  static constexpr Pixel<T, 3, Format::kRGB> Apply(const Pixel<T, 2, format> &src) noexcept {
    return {src[0], src[0], src[0]};
  }
};

template<>
struct PixelConversation<Format::kYA, Format::kGBR> {
  template<typename T, Format format>
  static constexpr Pixel<T, 3, Format::kGBR> Apply(const Pixel<T, 2, format> &src) noexcept {
    return {src[0], src[0], src[0]};
  }
};

template<>
struct PixelConversation<Format::kYA, Format::kRGBA> {
  template<typename T, Format format>
  static constexpr Pixel<T, 4, Format::kRGBA> Apply(const Pixel<T, 2, format> &src) noexcept {
    return {src[0], src[0], src[0], src[1]};
  }
};

template<>
struct PixelConversation<Format::kYA, Format::kBGRA> {
  template<typename T, Format format>
  static constexpr Pixel<T, 4, Format::kBGRA> Apply(const Pixel<T, 2, format> &src) noexcept {
    return {src[0], src[0], src[0], src[1]};
  }
};

template<>
struct PixelConversation<Format::kYA, Format::kABGR> {
  template<typename T, Format format>
  static constexpr Pixel<T, 4, Format::kABGR> Apply(const Pixel<T, 2, format> &src) noexcept {
    return {src[1], src[0], src[0], src[0]};
  }
};

template<>
struct PixelConversation<Format::kYA, Format::kARGB> {
  template<typename T, Format format>
  static constexpr Pixel<T, 4, Format::kARGB> Apply(const Pixel<T, 2, format> &src) noexcept {
    return {src[1], src[0], src[0], src[0]};
  }
};

// kRGB -> ?

template<>
struct PixelConversation<Format::kRGB, Format::kRGB> {
  template<typename T, Format format>
  static constexpr Pixel<T, 3, Format::kRGB> Apply(const Pixel<T, 3, format> &src) noexcept {
    return src;
  }
};

template<>
struct PixelConversation<Format::kRGB, Format::kY> {
  template<typename T, Format format, std::enable_if<std::is_integral_v<T>>>
  static constexpr Pixel<T, 1, Format::kY> Apply(const Pixel<T, 3, format> &src) noexcept {
    return {internal::ApproximateLinearCombination<T, 3, RGBToYCoefficients>(src)};
  }

  template<typename T, Format format, std::enable_if<std::is_floating_point_v<T>>>
  static constexpr Pixel<T, 1, Format::kY> Apply(const Pixel<T, 3, format> &src) noexcept {
    return {internal::LinearCombination<T, 3, RGBToYCoefficients>(src)};
  }
};
}
}

#endif //IMG_INCLUDE_IMG_PIXEL_CONVERSATIONS_H_
