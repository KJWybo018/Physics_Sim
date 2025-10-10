cmake_minimum_required(VERSION 3.12)
project(PhysicsSim)

set(CMAKE_CXX_STANDARD 17)

# pybind11 setup
find_package(pybind11 REQUIRED)

# Include directories
include_directories(cpp_engine)

# Add subdirectories
add_subdirectory(cpp_engine)
add_subdirectory(bindings)
