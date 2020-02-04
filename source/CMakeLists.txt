add_library(ToolBase STATIC WinMain.cpp TBApplication.cpp TBMessageBox.cpp TBWidget.cpp)

add_definitions(-DWIN32)

target_include_directories(ToolBase PUBLIC ${PROJECT_SOURCE_DIR}/include)