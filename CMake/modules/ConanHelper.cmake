IF (BUILD_EXAMPLES OR BUILD_TESTS)
  IF (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    INCLUDE(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    CONAN_BASIC_SETUP()
  ELSE ()
    MESSAGE(FATAL_ERROR
            "The file conanbuildinfo.cmake doesn't exist,
             you have to run conan install first")
  ENDIF ()

  # Library name of conan fmt is unclear,
  # so workaround to avoid linkage issue:
  ADD_COMPILE_OPTIONS(-DFMT_HEADER_ONLY=1)
ENDIF ()