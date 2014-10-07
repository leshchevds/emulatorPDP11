#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T22:52:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = emul
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    EmulatorPDP11.cpp \
    decoder.cpp

HEADERS  += mainwindow.h \
    EmulatorPDP11.h \
    decoder.h

FORMS    += mainwindow.ui
