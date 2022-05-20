
#qt_add_library(pie STATIC)

qt_add_qml_module(pie
    URI Pie
    VERSION 1.0
    QML_FILES PieObj.qml
    SOURCES
    pie.cpp pie.h
    antrender.cpp antrender.h
)


target_link_libraries(pie PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
    antlib
)
