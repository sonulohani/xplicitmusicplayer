#-------------------------------------------------
#
# Project created by QtCreator 2016-08-06T16:38:57
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XplicitMusicPlayer
TEMPLATE = app


SOURCES += main.cpp\
        xmpmainwindow.cpp \
    xmphelperclass.cpp

HEADERS  += xmpmainwindow.h \
    xmphelperclass.h \
    macros.h

FORMS    += xmpmainwindow.ui

RESOURCES += \
    icons.qrc
