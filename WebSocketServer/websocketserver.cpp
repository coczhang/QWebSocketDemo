#include "websocketserver.h"

#include <QDebug>

WebSocketServer::WebSocketServer(QObject *parent) : QObject(parent)
{
    initSocketConnect();
}

WebSocketServer::~WebSocketServer()
{
    m_pWebSocket->close();

    if (m_pWebSocket != NULL) {
        delete m_pWebSocket;
        m_pWebSocket = NULL;
    }
}

void WebSocketServer::onNewConnection()
{
    m_pWebSocket = m_pWebSocketServer->nextPendingConnection();
    connect(m_pWebSocket, &QWebSocket::textMessageReceived, this, &WebSocketServer::onTextMessageReived);
    connect(m_pWebSocket, &QWebSocket::disconnected, this, &WebSocketServer::onDisconnected);
}

void WebSocketServer::onTextMessageReived(const QString &message)
{
    emit sigTextMessage(message);
}

void WebSocketServer::onDisconnected()
{
    emit sigDisconnected();
}

void WebSocketServer::initSocketConnect()
{
    m_pWebSocketServer = new QWebSocketServer("Server", QWebSocketServer::NonSecureMode);
    if (m_pWebSocketServer != NULL) {
        m_pWebSocketServer->listen(QHostAddress::AnyIPv4, 8888);
    }

    connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
}

void WebSocketServer::closeWebServer()
{
    if (m_pWebSocketServer->isListening()) {
        m_pWebSocketServer->close();
    }
}

void WebSocketServer::sendTextMessage(QString info)
{
    m_pWebSocket->sendTextMessage(info);
}
