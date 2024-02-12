cmake_minimum_required(VERSION 3.17)
project(editor)

set(CMAKE_CXX_STANDARD 20)
set(
        CMAKE_CXX_FLAGS
        #"${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic"
)
find_package(wxWidgets REQUIRED core base stc)
include(${wxWidgets_USE_FILE})

if(APPLE)
    set(MACOSX_BUNDLE_ICON_FILE logo_hx_osx_ico.icns)
    set(app_ICON ${CMAKE_CURRENT_SOURCE_DIR}/assets/icons/logo_hx_osx_ico.icns)
    set_source_files_properties(${app_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif()
add_executable(
    editor MACOSX_BUNDLE
    MainEditorFrame.cpp
    Constants.hpp
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
    ${app_ICON}
)

target_link_libraries(editor ${wxWidgets_LIBRARIES})