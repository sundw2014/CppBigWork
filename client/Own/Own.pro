#-------------------------------------------------
#
# Project created by QtCreator 2015-09-02T10:25:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Own
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    own1.cpp \
    own2.cpp \
    AI.cpp \
    Zobrist.cpp

HEADERS  += widget.h \
    own1.h \
    own2.h \
    AI.h \
    mType.h \
    Zobrist.h

FORMS    += widget.ui \
    own1.ui \
    own2.ui

QT +=multimedia
