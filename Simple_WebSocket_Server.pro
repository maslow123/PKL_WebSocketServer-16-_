QT += core websockets
QT -= gui

CONFIG += c++11

TARGET = Simple_WebSocket_Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    worker.cpp

HEADERS += \
    worker.h
