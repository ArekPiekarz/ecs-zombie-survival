cmake_minimum_required(VERSION 3.8)
project(ecs-zombie-survival CXX)
set(CMAKE_CXX_STANDARD 17)
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
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${TARGET_NAME} PRIVATE
        -Weverything
        -Wno-c++98-compat
        -Wno-global-constructors
        -Wno-shadow-field-in-constructor
        -Wno-switch-enum
        -Wno-missing-prototypes
        -Wno-padded
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${TARGET_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
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
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${TEST_TARGET_NAME} PRIVATE
        -Weverything
        -Wno-c++98-compat
        -Wno-global-constructors
        -Wno-shadow-field-in-constructor
        -Wno-switch-enum
        -Wno-missing-prototypes
        -Wno-padded
        -Wno-weak-vtables
        -Werror
        -fsanitize=address
    )
    target_link_libraries(${TEST_TARGET_NAME}
        asan
        CONAN_PKG::entt
        CONAN_PKG::gtest
        CONAN_PKG::sfml
        CONAN_PKG::spdlog
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(${TEST_TARGET_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -fsanitize=address
        -fsanitize=undefined
    )
    target_link_libraries(${TEST_TARGET_NAME}
        asan
        ubsan
        CONAN_PKG::entt
        CONAN_PKG::gtest
        CONAN_PKG::sfml
        CONAN_PKG::spdlog
    )
endif()

target_include_directories(${TEST_TARGET_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
