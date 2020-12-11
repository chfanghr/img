CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
PROJECT(img)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED true)
SET(CMAKE_CXX_EXTENSIONS OFF)

SET(CMAKE_MODULE_PATH
        ${CMAKE_SOURCE_DIR}/CMake/modules/)

INCLUDE(Options)
INCLUDE(ConanHelper)
INCLUDE(PlatformHelper)
INCLUDE(TestHelper)

INCLUDE_DIRECTORIES(include)

SET(PIXEL_HEADERS
        include/img/pixel/format.h
        include/img/pixel/pixel.h
        include/img/pixel/traits.h
        include/img/pixel/conversations.h)

SET(INTERNAL_HEADERS
        include/img/internal/explicit_type.h
        include/img/internal/promote.h
        include/img/internal/round.h
        include/img/internal/type_traits.h
        include/img/internal/utils.h)

SET(IMG_HEADERS
    include/img/fmt.h
    include/img/basic_types.h
    include/img/math.h
    include/img/types.h)

SET(STD_HEADERS
        <type_traits>
        <cstdlib>
        <cstdint>
        <array>
        <vector>
        <cmath>)

ADD_LIBRARY(img
        ${PIXEL_HEADERS}
        ${INTERNAL_HEADERS}
        ${IMG_HEADERS}
        # dev: workaround linker language
        src/placeholder.cc)

TARGET_PRECOMPILE_HEADERS(img
        PUBLIC
        ${IMG_HEADERS}
        PRIVATE
        ${PIXEL_HEADERS}
        ${INTERNAL_HEADERS}
        ${STD_HEADERS})

IF (BUILD_TESTS)
ENDIF ()
