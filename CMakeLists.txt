cmake_minimum_required(VERSION 2.8)
project(ToolBase)

add_definitions(-DWIN32)

add_subdirectory(test)

add_library(ToolBase STATIC source/WinMain.cpp source/TBApplication.cpp source/TBMessageBox.cpp source/TBWidget.cpp source/TBTime.cpp)

target_include_directories(ToolBase PUBLIC ${PROJECT_SOURCE_DIR}/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)
set(INSTALL_INC_DIR ${CMAKE_INSTALL_PREFIX}/include)

install(TARGETS ToolBase 
		ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
		LIBRARY DESTINATION ${INSTALL_LIB_DIR})