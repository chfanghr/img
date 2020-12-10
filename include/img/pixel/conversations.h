//
// Created by 方泓睿 on 12/10/20.
//

#ifndef IMG_INCLUDE_IMG_PIXEL_CONVERSATIONS_H_
#define IMG_INCLUDE_IMG_PIXEL_CONVERSATIONS_H_

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
constexpr auto Convert(const PixelSrc &src, const Element& alpha) noexcept;

template<typename T, std::size_t N>
constexpr Pixel<T, N> YToNChannel(const Pixel<T, 1>& src) noexcept;
}

#endif //IMG_INCLUDE_IMG_PIXEL_CONVERSATIONS_H_
