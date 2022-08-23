
QT += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebSocketServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    websocketserver.cpp

HEADERS  += mainwindow.h \
    websocketserver.h
