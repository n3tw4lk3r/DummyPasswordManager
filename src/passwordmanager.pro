TARGET = Sample

QT = core gui
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
SOURCES += \
    main.cpp \
    MainWindow.cpp \
    FileOpenDialog.cpp

HEADERS += \
    MainWindow.hpp \
    FileOpenDialog.hpp
