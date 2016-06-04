#-------------------------------------------------
#
# Project created by QtCreator 2016-05-30T13:04:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Checkers_v2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    board.cpp \
    gamepainter.cpp \
    controller.cpp

HEADERS  += mainwindow.h \
    board.h \
    gamepainter.h \
    controller.h

FORMS    += mainwindow.ui


CONFIG += c++11
