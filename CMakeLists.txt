cmake_minimum_required(VERSION 3.17)
project(ecs-zombie-survival CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


### Dependencies

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake")
endif()
include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_check()
conan_add_remote(NAME bincrafters URL https://api.bintray.com/conan/bincrafters/public-conan)

conan_cmake_run(
    REQUIRES
        backward-cpp/1.5
        entt/3.4.0
        gtest/1.10.0
        magic_enum/0.6.6
        sfml/2.5.1@bincrafters/stable
        spdlog/1.6.1
    OPTIONS
        sfml:audio=False
        sfml:graphics=True
        sfml:network=False
        sfml:window=True
    BASIC_SETUP
    CMAKE_TARGETS
    BUILD outdated)


### Compile options

# Enable Link Time Optimization
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

# Enable STL debug assertions
# (https://gcc.gnu.org/onlinedocs/libstdc++/manual/debug_mode_semantics.html)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(_GLIBCXX_DEBUG=1 _GLIBCXX_DEBUG_PEDANTIC=1)
endif()

# Enable overflow checks for STD functions operating on arrays
# (https://access.redhat.com/blogs/766093/posts/1976213)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(_FORTIFY_SOURCE=2)
endif()


### Sources

set(TARGET_NAME ${CMAKE_PROJECT_NAME})
add_executable(${TARGET_NAME}
    core/game.cpp
    setup/logger-setup.cpp
    setup/survivor-renderer-setup.cpp
    setup/survivor-setup.cpp
    setup/texture-loader.cpp
    setup/window.cpp
    setup/zombie-renderer-setup.cpp
    setup/zombie-setup.cpp
    systems/isystem.cpp
    systems/looped-animator.cpp
    systems/sprite-renderer.cpp
    main.cpp
)

set(GCC_COMPILE_OPTIONS
    # Generic flags (https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html):
    -fstrict-aliasing
    -fstack-protector
    -Wall
    -Wextra
    -Wpedantic
    -Wdouble-promotion
    -Wformat=2
    -Wformat-overflow=2
    -Wformat-signedness
    -Wformat-truncation=2
    -Wnull-dereference
    -Wimplicit-fallthrough=5
    -Wmissing-include-dirs
    -Wunused-const-variable=1
    -Wstrict-aliasing=1
    -Wstrict-overflow=5
    -Wstringop-overflow=4
    -Walloc-zero
    -Walloca
    -Warith-conversion
    -Warray-bounds=2
    -Wattribute-alias=2
    -Wduplicated-branches
    -Wduplicated-cond
    -Wtrampolines
    -Wfloat-equal
    -Wshadow=local
    -Wunsafe-loop-optimizations
    -Wundef
    -Wunused-macros
    -Wcast-qual
    -Wcast-align=strict
    -Wconversion
    -Wdate-time
    -Wsign-conversion
    -Wlogical-op
    -Wno-aggressive-loop-optimizations
    -Wno-multichar
    -Wnormalized=nfc
    -Wodr
    -Wpacked
    -Wredundant-decls
    -Winline
    -Winvalid-pch
    -Wlong-long
    -Wvector-operation-performance
    -Wvla
    -Wdisabled-optimization
    -Wstack-protector
    # C++ specific flags (https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html):
    -fchar8_t
    -fno-nonansi-builtins
    -fnothrow-opt
    -fno-rtti
    -fstrict-enums
    -fuse-cxa-atexit
    -fvisibility-inlines-hidden
    -Wabi-tag
    -Wctor-dtor-privacy
    -Wdeprecated-copy-dtor
    -Wnoexcept
    -Wclass-memaccess
    -Wnon-virtual-dtor
    -Wredundant-tags
    -Wstrict-null-sentinel
    -Wold-style-cast
    -Woverloaded-virtual
    -Wzero-as-null-pointer-constant
    -Waligned-new=all
    -Wplacement-new=2
    -Wconditionally-supported
    -Wextra-semi
    -Wsuggest-final-types
    -Wsuggest-final-methods
    -Wsuggest-override
    -Wuseless-cast
)

set(CLANG_COMPILE_OPTIONS
    -Weverything
    -Wno-c++98-compat
    -Wno-global-constructors
    -Wno-shadow-field-in-constructor
    -Wno-switch-enum
    -Wno-missing-prototypes
    -Wno-padded
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${TARGET_NAME} PRIVATE ${GCC_COMPILE_OPTIONS})
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${TARGET_NAME} PRIVATE ${CLANG_COMPILE_OPTIONS})
endif()

target_link_libraries(${TARGET_NAME}
    CONAN_PKG::backward-cpp
    CONAN_PKG::entt
    CONAN_PKG::magic_enum
    CONAN_PKG::sfml
    CONAN_PKG::spdlog
)

target_include_directories(${TARGET_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)


### Tests

set(TEST_TARGET_NAME ${TARGET_NAME}-test)
add_executable(${TEST_TARGET_NAME}
    setup/logger-setup.cpp
    systems/isystem.cpp
    systems/looped-animator.cpp
    systems/tests/looped-animator-tests.cpp
    tests.cpp
)

set(LIBS_LINKED_TO_TESTS
    asan
    CONAN_PKG::entt
    CONAN_PKG::gtest
    CONAN_PKG::sfml
    CONAN_PKG::spdlog
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${TEST_TARGET_NAME} PRIVATE
        ${GCC_COMPILE_OPTIONS}
        -fsanitize=address
        -fsanitize=undefined
    )
    target_link_libraries(${TEST_TARGET_NAME} ${LIBS_LINKED_TO_TESTS} ubsan)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${TEST_TARGET_NAME} PRIVATE
        ${CLANG_COMPILE_OPTIONS}
        -Wno-weak-vtables
        -fsanitize=address
    )
    target_link_libraries(${TEST_TARGET_NAME} ${LIBS_LINKED_TO_TESTS})
endif()

target_include_directories(${TEST_TARGET_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
