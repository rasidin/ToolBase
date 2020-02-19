cmake_minimum_required(VERSION 3.1)

enable_testing()

add_executable(ToolBaseTest test.cpp)
target_link_libraries(ToolBaseTest ToolBase)
include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
