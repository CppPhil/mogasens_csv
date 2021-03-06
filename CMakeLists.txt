include(FetchContent)

cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(mogasens_csv VERSION 1.0.0)

enable_testing()

if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    string(APPEND CMAKE_CXX_FLAGS "/W4")
  endif()

  string(
    APPEND
    CMAKE_CXX_FLAGS
    " /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS /D_SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING /DNOMINMAX /D_UNICODE /DUNICODE"
  )

  string(APPEND CMAKE_CXX_FLAGS_DEBUG " /Od /DDEBUG_MODE")
  string(APPEND CMAKE_CXX_FLAGS_RELEASE " /O2 /DNDEBUG /DRELEASE_MODE")
else()
  string(
    APPEND
    CMAKE_CXX_FLAGS
    " -fwrapv -Werror -Wall -Wextra -Wstrict-aliasing -Wcast-align -Wmissing-include-dirs -Wpointer-arith -Wunreachable-code -Wunused -Wunused-parameter -Wno-uninitialized -Wno-deprecated-copy -Wno-aggressive-loop-optimizations -Wno-implicit-fallthrough"
  )

  string(APPEND CMAKE_CXX_FLAGS_DEBUG " -g -O0 -DDEBUG_MODE")
  string(APPEND CMAKE_CXX_FLAGS_RELEASE " -g -O3 -DNDEBUG -DRELEASE_MODE")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

find_package(Threads REQUIRED)

add_subdirectory(external/fmtlib)
add_subdirectory(external/googletest)
add_subdirectory(external/scnlib)
add_subdirectory(external/philslib)

add_subdirectory(csv_lib)
add_subdirectory(fix_csv)
add_subdirectory(counting)
add_subdirectory(compare_segmentation)
add_subdirectory(confusion_matrix)
add_subdirectory(feature_extraction)
