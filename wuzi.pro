#-------------------------------------------------
#
# Project created by QtCreator 2017-02-24T21:19:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wuzi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    chessboard.cpp \
    chesslocation.cpp \
    winning.cpp

HEADERS  += mainwindow.h \
    chessboard.h \
    chesslocation.h \
    winning.h

FORMS    += mainwindow.ui \
    winning.ui

RESOURCES += \

