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

ADD_LIBRARY(img
            include/img/pixel/format.h
            include/img/pixel/pixel.h
            include/img/internal/promote.h
            include/img/types.h
            include/img/fmt.h
            include/img/internal/explicit_type.h
            include/img/pixel/traits.h
            include/img/internal/utils.h
            include/img/pixel/conversations.h
            # dev: workaround linker language
            src/placeholder.cc include/img/internal/round.h include/img/internal/type_traits.h)

TARGET_PRECOMPILE_HEADERS(img PUBLIC
                          include/img/pixel/format.h
                          include/img/pixel/pixel.h
                          include/img/internal/promote.h
                          include/img/types.h
                          include/img/fmt.h
                          include/img/internal/explicit_type.h
                          include/img/pixel/traits.h
                          include/img/internal/utils.h
                          include/img/pixel/conversations.h
                          include/img/internal/round.h
                          PRIVATE
                          <cstdint>
                          <cstdlib>
                          <cmath>
                          <array>
                          <vector>
                          <type_traits>
                          )
IF (BUILD_TESTS)
ENDIF ()
