#-------------------------------------------------
#
# Project created by QtCreator 2017-07-25T20:56:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += C++14
TARGET = ffayno
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tabbutton.cpp \
    tabcontenttreeview.cpp \
    tabscontroller.cpp

HEADERS  += mainwindow.h \
    tabbutton.h \
    tabcontenttreeview.h \
    tabscontroller.h

FORMS    += mainwindow.ui
