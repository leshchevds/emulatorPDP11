#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T22:52:47
#
#-------------------------------------------------

QT       += core gui
QT       += concurrent

CONFIG  += c++11

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
    decoder.h \
    tab.inc \
    decoders.inc \
    operations.inc \
    modes_selector.inc

FORMS    += mainwindow.ui
