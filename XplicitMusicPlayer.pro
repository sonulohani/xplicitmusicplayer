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
        XMPMainWindow.cpp \
    XMPHelperClass.cpp \
    XMPPlaylist.cpp \
	XMPMediaPlayer.cpp

HEADERS  += XMPMainWindow.h \
    XMPHelperClass.h \
    Macros.h \
    XMPPlaylist.h \
	XMPMediaPlayer.h

FORMS    += XMPMainWindow.ui

RESOURCES += \
    icons.qrc
