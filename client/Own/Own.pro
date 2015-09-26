#-------------------------------------------------
#
# Project created by QtCreator 2015-09-02T10:25:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Own
TEMPLATE = app

CONFIG += c++11//
CONFIG += console

LIBS += ws2_32.lib

SOURCES += main.cpp\
        widget.cpp \
    own1.cpp \
    own2.cpp \
    own3.cpp \
    own4.cpp \
    own5.cpp \
    own6.cpp \
    own7.cpp \
    AI.cpp \
    client.cpp \
    protocol.cpp \
    roomlist.cpp \
    statemachine.cpp \
    Zobrist.cpp \
    mythread.cpp \
    login.cpp

    HEADERS  += widget.h \
    own1.h \
    own2.h \
    own3.h \
    own4.h \
    own5.h \
    own6.h \
    own7.h \
    AI.h \
    mType.h \
    client.hpp \
    protocol.hpp \
    roomlist.h \
    statemachine.h \
    Zobrist.h \
    mythread.h \
    login.h

FORMS    += widget.ui \
    own1.ui \
    own2.ui \
    own3.ui \
    own4.ui \
    own5.ui \
    own6.ui \
    own7.ui \
    roomlist.ui \
    login.ui

QT +=multimedia

