
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
CONFIG += C++11
TARGET = traficcounting
INCLUDEPATH +=-I/usr/local/include

LIBS += `pkg-config opencv --libs --cflags`
SOURCES += \
    main.cpp \
    window.cpp \
    videofromfile.cpp \
    font.cpp \
    timecalc.cpp \
    fps.cpp

HEADERS += \
    window.h \
    videofromfile.h \
    font.h \
    timecalc.h \
    fps.h
