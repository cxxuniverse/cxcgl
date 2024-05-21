cmake_minimum_required(VERSION 3.20)

project(
    CXCGL
    VERSION 0.10
    DESCRIPTION "CXCGL - Graphics Library in C"
    LANGUAGES C)

include_directories(include)

add_executable(main src/main.c)
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

target_compile_features(main PRIVATE c_std_17)
target_compile_options(main PRIVATE -g -Wall -Wextra)