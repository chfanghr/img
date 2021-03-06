//
// Created by 方泓睿 on 12/10/20.
//

#ifndef IMG_INCLUDE_IMG_INTERNAL_FMT_H_
#define IMG_INCLUDE_IMG_INTERNAL_FMT_H_

#include <string>

namespace img {
template<typename T>
std::string Display(const T &);

template<typename T>
std::string DebugDisplay(const T &);
}
#endif //IMG_INCLUDE_IMG_INTERNAL_FMT_H_
