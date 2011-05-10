#-------------------------------------------------
#
# Project created by QtCreator 2011-05-06T19:08:04
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = book2pod
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Spitter.cpp \
    PodExceptions.cpp \
    Buffer.cpp

OTHER_FILES += \
    master.txt

HEADERS += \
    Splitter.h \
    PodExceptions.h \
    main.h \
    Buffer.h
