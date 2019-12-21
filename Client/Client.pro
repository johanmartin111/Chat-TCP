#-------------------------------------------------
#
# Project created by QtCreator 2016-02-08T15:15:38
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    structs/chat.cpp \
    structs/client.cpp \
    structs/mensaje.cpp \
    structs/peticion.cpp \
    structs/server.cpp \
    structs/usuario.cpp \
    chatwindow.cpp

HEADERS  += mainwindow.h \
    structs/chat.h \
    structs/client.h \
    structs/mensaje.h \
    structs/peticion.h \
    structs/server.h \
    structs/usuario.h \
    chatwindow.h


FORMS    += mainwindow.ui \
    chatwindow.ui
