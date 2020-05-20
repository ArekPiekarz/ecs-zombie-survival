cmake_minimum_required(VERSION 3.8)
project(ecs-zombie-survival CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
        magic_enum/0.6.5
        sfml/2.5.1@bincrafters/stable
        spdlog/1.6.0
    OPTIONS
        sfml:graphics=True
        sfml:window=True
    BASIC_SETUP
    CMAKE_TARGETS
    BUILD outdated)

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
    systems/looped-animator.cpp
    systems/sprite-renderer.cpp
    main.cpp)
target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic)
target_link_libraries(${TARGET_NAME}
    CONAN_PKG::backward-cpp
    CONAN_PKG::entt
    CONAN_PKG::magic_enum
    CONAN_PKG::sfml
    CONAN_PKG::spdlog)
target_include_directories(${TARGET_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

set(TEST_TARGET_NAME ${TARGET_NAME}-test)
add_executable(${TEST_TARGET_NAME}
    setup/logger-setup.cpp
    systems/looped-animator.cpp
    systems/tests/looped-animator-tests.cpp
    tests.cpp)
target_compile_options(${TEST_TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -fsanitize=address -fsanitize=undefined)
target_link_libraries(${TEST_TARGET_NAME}
    asan
    ubsan
    CONAN_PKG::entt
    CONAN_PKG::gtest
    CONAN_PKG::sfml
    CONAN_PKG::spdlog)
target_include_directories(${TEST_TARGET_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
