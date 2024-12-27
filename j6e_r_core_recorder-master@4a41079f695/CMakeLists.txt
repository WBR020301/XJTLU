cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Mf4Writer VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/mdf/include)

# Add subdirectories for outer layer and inner mdflib
add_subdirectory(src)          # Outer layer (your custom code)
add_subdirectory(mdflib)       # Inner layer (open-source code)

# Add the executable (this assumes your main.cpp is in the src/ directory)
add_executable(Mf4Writer main.cpp)

# 链接到 mdflib 和 utils
target_link_libraries(Mf4Writer PRIVATE mdflib utils)

