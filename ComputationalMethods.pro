#-------------------------------------------------
#
# Project created by QtCreator 2017-11-04T17:51:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ComputationalMethods
TEMPLATE = app


SOURCES += sample/main.cpp\
     gui/src/mainwindow.cpp \
     gui/src/matrixinputview.cpp \
     gui/src/mainwindowview.cpp \
     gui/src/control.cpp \
     lib/src/icomputionalmethods.cpp \
     lib/src/gaussmethod.cpp \
     lib/src/kramermethod.cpp \
     lib/src/seidelmethod.cpp \
     lib/src/simpleiterationmethod.cpp \
     lib/src/upperrelaxationmethod.cpp \
     gui/src/qanswerform.cpp \
     gui/src/qinputparamsline.cpp \






HEADERS  += gui/include/mainwindow.h \
    gui/include/matrixinputview.h \
    gui/include/mainwindowview.h \
    gui/include/control.h \
    lib/src/icomputionalmethods.h \
    lib/src/gaussmethod.h \
    lib/src/kramermethod.h \
    lib/src/seidelmethod.h \
    lib/src/simpleiterationmethod.h \
    upperrelaxationmethod.h \
    gui/include/qanswerform.h \
    gui/include/qinputparamsline.h

FORMS += forms/mainwindow.ui

DISTFILES += \
    ComputationalMethods.pro.IO4561
