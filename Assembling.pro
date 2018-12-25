#-------------------------------------------------
#
# Project created by QtCreator 2017-11-19T22:42:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Assembling
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    administrator.cpp \
    authorization.cpp \
    generator.cpp \
    configurations.cpp \
    componentsdb.cpp \
    componentslist.cpp \
    components/case.cpp \
    components/component.cpp \
    components/cooler.cpp \
    components/cpu.cpp \
    components/datastorage.cpp \
    components/gpu.cpp \
    components/motherboard.cpp \
    components/peripheral.cpp \
    components/psu.cpp \
    components/ram.cpp \
    settings.cpp \
    assembly.cpp

HEADERS  += mainwindow.h \
    administrator.h \
    authorization.h \
    generator.h \
    configurations.h \
    components/case.h \
    components/component.h \
    components/cooler.h \
    components/cpu.h \
    components/datastorage.h \
    components/gpu.h \
    components/motherboard.h \
    components/peripheral.h \
    components/psu.h \
    components/ram.h \
    componentsdb.h \
    componentslist.h \
    settings.h \
    partsenum.h \
    assembly.h

FORMS    += mainwindow.ui \
    administrator.ui \
    authorization.ui \
    generator.ui \
    configurations.ui

RC_FILE  = icon.rc
