# Define any additional source files for the outer layer (your code)
set(SOURCES
    # Add your source files here
    mtc_mcu_mf4_writer.cpp
)
# 添加 utils 目录中的源文件
add_subdirectory(utils)
# Add a library for the outer layer (optional, if needed)
add_library(mdf ${SOURCES})

# Link the outer library to mdflib
target_link_libraries(mdf PRIVATE mdflib)

# Include your custom headers if necessary
target_include_directories(mdf PRIVATE ${CMAKE_SOURCE_DIR}/include)
