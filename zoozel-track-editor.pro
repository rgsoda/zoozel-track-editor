#-------------------------------------------------
#
# Project created by QtCreator 2010-11-22T09:56:20
#
#-------------------------------------------------

QT       += core gui

TARGET = zoozel-track-editor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp

HEADERS  += mainwindow.h \
    scene.h

FORMS    += mainwindow.ui

LIBS += -lqjson
