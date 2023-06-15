#-------------------------------------------------
#
# Project created by QtCreator 2023-06-13T13:10:09
#
#-------------------------------------------------

QT       += core gui charts serialport network
#serialbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = swivelJoint
TEMPLATE = app

LIBS += -Ldll -lws2_32

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp \
    thread.cpp \
    src/modbus.c \
    src/modbus-data.c \
    src/modbus-rtu.c \
    src/modbus-tcp.c

HEADERS += \
        widget.h \
    thread.h \
    src/modbus.h \
    src/modbus-private.h \
    src/modbus-rtu.h \
    src/modbus-rtu-private.h \
    src/modbus-tcp.h \
    src/modbus-tcp-private.h \
    src/modbus-version.h

FORMS += \
        widget.ui

DISTFILES += \
    src/modbus.lib
