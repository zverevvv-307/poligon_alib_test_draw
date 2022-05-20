get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

file(GLOB SINGLETON_QML RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *Backend.qml
    *Singleton.qml
    )

file(GLOB QML_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.qml
    *.js
    *.mjs
    )

set_source_files_properties(
        ${SINGLETON_QML}
    PROPERTIES
        QT_QML_SINGLETON_TYPE true
    )


file(GLOB CPP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.cpp
    *.h
    )

#qt_add_library(${TARGET_NAME} STATIC)

qt_add_qml_module(${TARGET_NAME}
        URI ${TARGET_NAME}
        VERSION 1.0
        SOURCES ${CPP_SOURCES}
        QML_FILES ${QML_SOURCES}
)

target_link_libraries(${TARGET_NAME} PRIVATE
    Qt::Quick
    antlib
)

message("*** qt_add_qml_module: " ${TARGET_NAME})
