#-------------------------------------------------
#
# Project created by QtCreator 2017-12-23T18:09:15
#
#-------------------------------------------------

QT       -= core gui

TARGET = boxy-sync-core
TEMPLATE = lib
CONFIG += staticlib c++11
LIBS += -lsqlite3

SOURCES += ./src/boxysynccore.cpp \
    ./src/database.cpp \
    ./src/storage.cpp

HEADERS += ./include/boxysynccore.h \
    ./include/database.h \
    ./include/storage.h
#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
