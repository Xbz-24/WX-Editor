cmake_minimum_required(VERSION 3.17)
project(editor)
set(CMAKE_CXX_STANDARD 20)
find_package(wxWidgets REQUIRED core base stc)
include(${wxWidgets_USE_FILE})
add_executable(editor main_frame.cpp constants.hpp FindDialog.hpp FindDialog.cpp)
target_link_libraries(editor ${wxWidgets_LIBRARIES})