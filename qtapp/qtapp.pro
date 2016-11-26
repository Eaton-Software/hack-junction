#-------------------------------------------------
#
# Project created by QtCreator 2016-11-26T01:52:30
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtapp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    conversion.hpp

FORMS    += mainwindow.ui

CONFIG += link_pkgconfig

PKGCONFIG += opencv libcurl

INCLUDEPATH += cpr/include/cpr

SUBDIRS += cpr
