QT += core gui websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebSocketClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    websocketclient.cpp

HEADERS  += mainwindow.h \
    websocketclient.h
