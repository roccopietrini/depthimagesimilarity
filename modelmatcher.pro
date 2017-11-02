QT += core
QT -= gui

CONFIG += c++11

TARGET = modelmatcher
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

LIBS    += -lopencv_core -lopencv_imgproc -lopencv_highgui
