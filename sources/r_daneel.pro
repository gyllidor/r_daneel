#-------------------------------------------------
#
# Project created by QtCreator 2017-07-25T20:56:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += C++14
TARGET = r_daneel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tabbutton.cpp \
    tabcontenttreeview.cpp \
    tabscontroller.cpp \
    pathbarview.cpp

HEADERS  += mainwindow.h \
    tabbutton.h \
    tabcontenttreeview.h \
    tabscontroller.h \
    pathbarview.h

FORMS    += mainwindow.ui

RESOURCES += \
    stylesheets.qrc
