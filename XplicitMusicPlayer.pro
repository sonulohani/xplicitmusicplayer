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
        XMPVolumeSlider.cpp \
	XMPPlaylistModel.cpp \
        XMPPlaylistView.cpp

HEADERS  += XMPMainWindow.hpp \
    XMPHelperClass.hpp \
    Macros.hpp \
    XMPPlaylist.hpp \
	XMPVolumeSlider.hpp \
	XMPPlaylistModel.hpp \
	XMPPlaylistView.hpp

FORMS    += XMPMainWindow.ui

RESOURCES += \
    icons.qrc


unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -L/usr/lib/ -lz -ltag

INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include

unix: PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/libtag.a
