cmake_minimum_required(VERSION 3.17)
project(editor)

set(CMAKE_CXX_STANDARD 20)
set(
        CMAKE_CXX_FLAGS
        #"${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic"
)
find_package(wxWidgets REQUIRED core base stc)
include(${wxWidgets_USE_FILE})

add_executable(
        editor
        MainEditorFrame.cpp
        constants.hpp
        FindDialog.hpp
        FindDialog.cpp
        FileOperations.cpp
        FileOperations.hpp
        MainEditorFrame.hpp
        app.cpp
        app.hpp
        EditorComponent.cpp
        EditorComponent.hpp
        ToolbarComponent.cpp
        ToolbarComponent.hpp
        StatusBarComponent.cpp
        StatusBarComponent.hpp
        EventBindingComponent.cpp
        EventBindingComponent.hpp
        LayoutComponent.cpp
        LayoutComponent.hpp
        FileManagerComponent.cpp
        FileManagerComponent.hpp
)
target_link_libraries(editor ${wxWidgets_LIBRARIES})