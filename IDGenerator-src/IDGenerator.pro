#-------------------------------------------------
#
# Project created by QtCreator 2016-06-01T16:47:44
#
#-------------------------------------------------

QT       += core gui

win32:RC_ICONS += id_generator_icon.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IDGenerator
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

CONFIG += static
static { #// Everything below takes effect with CONFIG += static
    CONFIG += static
#    QTPLUGIN += qsqloci qgif
    DEFINES += STATIC #// Equivalent to "#define STATIC" in source code
    message("Static build.")
}

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -Os
