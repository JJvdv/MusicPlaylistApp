QT += gui
QT += widgets
QT += xml
QT += network

TARGET = Playlist
TEMPLATE = app

CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
        filereader.cpp \
        filewriter.cpp \
        listreader.cpp \
        listwriter.cpp \
        login.cpp \
        main.cpp \
        music.cpp \
        musicinput.cpp \
        musictablemodel.cpp \
        musicview.cpp

HEADERS += \
    filereader.h \
    filewriter.h \
    listreader.h \
    listwriter.h \
    login.h \
    music.h \
    musicinput.h \
    musictablemodel.h \
    musicview.h

