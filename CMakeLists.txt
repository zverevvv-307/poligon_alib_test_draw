cmake_minimum_required(VERSION 3.20)

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project( ${TARGET_NAME} VERSION 22.7 LANGUAGES CXX )

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)


find_package(Qt6 REQUIRED COMPONENTS Widgets Quick)

add_subdirectory (antlib)
add_subdirectory (VxAnt)


qt_add_executable(app_poligon
    main.cpp
)

qt_add_qml_module(app_poligon
    URI poligon
    VERSION 1.0
    QML_FILES main.qml 
)

set_target_properties(app_poligon PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(app_poligon
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(app_poligon  PRIVATE
    Qt6::Widgets
    Qt6::Quick
)

