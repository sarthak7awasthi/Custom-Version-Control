cmake_minimum_required(VERSION 3.10)

# Project name and version
project(VCS VERSION 1.0)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable for VCS
add_executable(vcs
    src/vcs.cpp
    src/init.cpp
    src/track.cpp
    src/commit.cpp
    src/log.cpp
    src/checkout.cpp
)


target_include_directories(vcs PUBLIC "${PROJECT_SOURCE_DIR}/include")


find_package(OpenSSL REQUIRED)
target_link_libraries(vcs OpenSSL::Crypto)
