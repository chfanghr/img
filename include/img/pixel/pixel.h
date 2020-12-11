//
// Created by 方泓睿 on 12/10/20.
//

#ifndef IMG_INCLUDE_IMG_PIXEL_PIXEL_H_
#define IMG_INCLUDE_IMG_PIXEL_PIXEL_H_

#include <array>

#include "format.h"
#include "../internal/promote.h"
#include "../fmt.h"

namespace img {
namespace pixel {
template<typename T, std::size_t nr_channels_, Format format_ = Format::kUnknown>
class Pixel {
 public:
  using ValueType = T;

  static constexpr std::size_t kNrChannels = nr_channels_;
  static constexpr Format kFormat = format_;

  using PixelType = Pixel;
  using ConstPixelType = const Pixel;

  ~Pixel() = default;

  constexpr Pixel() noexcept = default;
  constexpr Pixel(const Pixel &) = default;
  constexpr Pixel &operator=(const Pixel &) = default;
  constexpr Pixel(Pixel &&) noexcept = default;
  constexpr Pixel &operator=(Pixel &&) noexcept = default;

  template<typename... Args, typename = std::enable_if_t<sizeof...(Args) == nr_channels_>>
  constexpr explicit Pixel(Args &&... args) noexcept: data_({std::forward<T>(args)...}) {
    static_assert(std::is_trivial_v<Pixel>, "pixel type is not trivial");
    static_assert((std::is_standard_layout_v<Pixel>), "pixel type is not standard layout");
    static_assert(sizeof(Pixel) == nr_channels_ * sizeof(T), "Pixel class is not tightly packed");
  };

  constexpr explicit Pixel(const std::array<T, nr_channels_> &other) noexcept: data_(other) {
    static_assert(std::is_trivial_v<Pixel>, "pixel type is not trivial");
    static_assert((std::is_standard_layout_v<Pixel>), "pixel type is not standard layout");
    static_assert(sizeof(Pixel) == nr_channels_ * sizeof(T), "Pixel class is not tightly packed");
  }
  template<typename U>
  constexpr explicit Pixel(const std::array<U, nr_channels_> &arr) {
    static_assert(std::is_trivial_v<Pixel>, "pixel type is not trivial");
    static_assert((std::is_standard_layout_v<Pixel>), "pixel type is not standard layout");
    static_assert(sizeof(Pixel) == nr_channels_ * sizeof(T), "Pixel class is not tightly packed");
    for (std::size_t i = 0; i < nr_channels_; i++)
      data_[i] = static_cast<T>(arr[i]);
  }

  template<typename U>
  constexpr explicit Pixel(const Pixel<U, nr_channels_> &other) {
    static_assert(std::is_trivial_v<Pixel>, "pixel type is not trivial");
    static_assert((std::is_standard_layout_v<Pixel>), "pixel type is not standard layout");
    static_assert(sizeof(Pixel) == nr_channels_ * sizeof(T), "Pixel class is not tightly packed");
    for (std::size_t i = 0; i < nr_channels_; i++)
      (*this)[i] = static_cast<T>(other[i]);
  }
  template<typename U>
  constexpr Pixel &operator=(const Pixel<U, nr_channels_> &other) {
    static_assert(std::is_trivial_v<Pixel>, "pixel type is not trivial");
    static_assert((std::is_standard_layout_v<Pixel>), "pixel type is not standard layout");
    static_assert(sizeof(Pixel) == nr_channels_ * sizeof(T), "Pixel class is not tightly packed");
    for (std::size_t i = 0; i < nr_channels_; i++)
      (*this)[i] = static_cast<T>(other[i]);
    return *this;
  }

  constexpr T *data() noexcept { return data_.data(); }
  [[nodiscard]] constexpr const T *data() const noexcept { return data_.data(); }

  constexpr T &operator[](std::size_t n) noexcept { return data_[n]; }
  constexpr const T &operator[](std::size_t n) const noexcept { return data_[n]; }

  template<typename = std::enable_if<nr_channels_ == 1>>
  constexpr explicit operator T() const noexcept { return data_[0]; }

  constexpr Pixel &operator+=(const Pixel &rhs) noexcept {
    for (std::size_t i = 0; i < nr_channels_; i++)
      (*this)[i] += rhs[i];
    return *this;
  }
  constexpr Pixel &operator-=(const Pixel &rhs) noexcept {
    for (std::size_t i = 0; i < nr_channels_; i++)
      (*this)[i] -= rhs[i];
    return *this;
  }
  constexpr Pixel &operator*=(const Pixel &rhs) noexcept {
    for (std::size_t i = 0; i < nr_channels_; i++)
      (*this)[i] *= rhs[i];
    return *this;
  }
  constexpr Pixel &operator/=(const Pixel &rhs) noexcept {
    for (std::size_t i = 0; i < nr_channels_; i++)
      (*this)[i] /= rhs[i];
    return *this;
  }

  template<typename U, Format format_1>
  struct CommonPixel {
    using Type = Pixel<std::common_type_t<T, U>, nr_channels_, format_1 == Format::kUnknown ? format_ : format_1>;
  };

  template<typename U, Format format_1>
  using CommonPixelType = typename CommonPixel<U, format_1>::Type;

  template<typename U, Format format_1>
  constexpr auto operator+(const Pixel<U, nr_channels_, format_1> &rhs) const noexcept {
    static_assert(format_1 == format_ ||
                      format_1 == Format::kUnknown ||
                      format_ == Format::kUnknown,
                  "Different pixel format");
    CommonPixelType<U, format_1> ret{*this};
    for (std::size_t i = 0; i < nr_channels_; i++)
      ret[i] += rhs[i];
    return ret;
  }
  template<typename U, Format format_1>
  constexpr auto operator-(const PixelType &rhs) const noexcept {
    static_assert(format_1 == format_ ||
                      format_1 == Format::kUnknown ||
                      format_ == Format::kUnknown,
                  "Different pixel format");
    CommonPixelType<U, format_1> ret{*this};
    for (std::size_t i = 0; i < nr_channels_; i++)
      ret[i] -= rhs[i];
    return ret;
  }
  template<typename U, Format format_1>
  constexpr auto operator*(const PixelType &rhs) const noexcept {
    static_assert(format_1 == format_ ||
                      format_1 == Format::kUnknown ||
                      format_ == Format::kUnknown,
                  "Different pixel format");
    CommonPixelType<U, format_1> ret{*this};
    for (std::size_t i = 0; i < nr_channels_; i++)
      ret[i] *= rhs[i];
    return ret;
  }
  template<typename U, Format format_1>
  constexpr auto operator/(const PixelType &rhs) const noexcept {
    static_assert(format_1 == format_ ||
                      format_1 == Format::kUnknown ||
                      format_ == Format::kUnknown,
                  "Different pixel format");
    CommonPixelType<U, format_1> ret{*this};
    for (std::size_t i = 0; i < nr_channels_; i++)
      ret[i] *= rhs[i];
    return ret;
  }

  constexpr Pixel &operator+=(const T &rhs) noexcept {
    for (std::size_t i = 0; i < nr_channels_; i++)
      (*this)[i] += rhs;
    return *this;
  }
  constexpr Pixel &operator-=(const T &rhs) noexcept {
    for (std::size_t i = 0; i < nr_channels_; i++)
      (*this)[i] -= rhs;
    return *this;
  }
  constexpr Pixel &operator*=(const T &rhs) noexcept {
    for (std::size_t i = 0; i < nr_channels_; i++)
      (*this)[i] *= rhs;
    return *this;
  }
  constexpr Pixel &operator/=(const T &rhs) noexcept {
    for (std::size_t i = 0; i < nr_channels_; i++)
      (*this)[i] /= rhs;
    return *this;
  }

  constexpr Pixel operator-() noexcept {
    Pixel ret{};
    for (std::size_t i = 0; i < nr_channels_; i++)
      ret[i] = -(*this)[i];
    return ret;
  }

  constexpr Pixel operator<<(std::size_t shift) const {
    Pixel ret{*this};
    for (std::size_t i = 0; i < nr_channels_; i++)
      ret[i] <<= shift;
    return ret;
  }
  constexpr Pixel operator>>(std::size_t shift) const {
    Pixel ret{*this};
    for (std::size_t i = 0; i < nr_channels_; i++)
      ret[i] <<= shift;
    return ret;
  }
  constexpr Pixel &operator<<=(std::size_t shift) const {
    for (std::size_t i = 0; i < nr_channels_; i++)
      (*this)[i] <<= shift;
    return *this;
  }
  constexpr Pixel &operator>>=(std::size_t shift) const {
    for (std::size_t i = 0; i < nr_channels_; i++)
      (*this)[i] <<= shift;
    return *this;
  }

  template<Format rhs_format>
  constexpr bool operator==(const Pixel<T, nr_channels_, rhs_format> &rhs) const noexcept {
    static_assert(rhs_format == format_ ||
                      rhs_format == Format::kUnknown ||
                      format_ == Format::kUnknown,
                  "Different pixel format");
    bool equal = true;
    for (std::size_t i = 0; i < nr_channels_; i++)
      equal &= (rhs[i] == (*this)[i]);
    return equal;
  }
  template<Format rhs_format>
  constexpr bool operator!=(const Pixel<T, nr_channels_, rhs_format> &rhs) const noexcept {
    return !this->operator==(rhs);
  }

  friend constexpr void swap(Pixel &rhs, Pixel &lhs) {
    for (size_t i = 0; i < nr_channels_; i++)
      std::swap(rhs.data_[i], lhs.data_[i]);
  }

  friend std::string Display(const Pixel &px) {
    using namespace std::literals;
    auto ret = "("s;
    for (std::size_t i = 0; i < nr_channels_ - 1; i++) {
      ret += std::to_string(internal::PromotedType<T>(px[i]));
      ret += ","s;
    }
    ret += std::to_string(internal::PromotedType<T>(px[nr_channels_ - 1]));
    ret += ")"s;
    return ret;
  }
 private:
  std::array<T, nr_channels_> data_;
};

template<typename PixelType, typename = void>
struct IsPixelType : std::false_type {};

template<typename PixelType>
struct IsPixelType<PixelType, std::void_t<
    typename PixelType::ValueType,
    decltype(std::declval<PixelType>().kNrChannels),
    decltype(std::declval<PixelType>().kFormat)
>> : std::true_type {
};

template<typename T>
constexpr bool kIsPixelType = IsPixelType<T>::value;
}

namespace internal {
template<typename T, std::size_t nr_channels_, pixel::Format format_>
struct Promote<pixel::Pixel<T, nr_channels_, format_>> {
  using Type = pixel::Pixel<Promote<T>, nr_channels_, format_>;
};
}
}

#endif //IMG_INCLUDE_IMG_PIXEL_PIXEL_H_
