# 获取 utils 目录下的所有源文件
file(GLOB UTILS_SOURCES *.cpp)

# 将 utils 源文件添加到一个静态库
add_library(utils STATIC ${UTILS_SOURCES})

# 设置 include 目录
target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/include/utils)

