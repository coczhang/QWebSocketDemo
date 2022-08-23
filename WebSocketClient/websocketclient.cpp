#include "websocketclient.h"

#include <QDebug>

WebSocketClient::WebSocketClient(QObject *parent) : QObject(parent),m_bConnected(false)
{
    init_socket_connect();
}

WebSocketClient::~WebSocketClient()
{
    if (m_pWebSocket != NULL) {
        delete m_pWebSocket;
        m_pWebSocket = NULL;
    }
}

void WebSocketClient::socketConnected()
{
    m_bConnected = true;

    connect(m_pWebSocket, &QWebSocket::textMessageReceived, this, &WebSocketClient::socketRecvTextMsg);
    connect(m_pWebSocket, &QWebSocket::binaryMessageReceived, this, &WebSocketClient::socketRecvBinaryMsg);

    emit sigConnected();
}

void WebSocketClient::disSocketConnected()
{
    emit sigDisconnected();
}

void WebSocketClient::socketRecvTextMsg(QString message)
{
    emit sigRecvTextMsg(message);
}

void WebSocketClient::socketRecvBinaryMsg(QByteArray message)
{
    qDebug() << "socketRecvBinaryMsg:" << message;
}

void WebSocketClient::socketError(QAbstractSocket::SocketError error)
{
    qDebug() << "socketError:" << (int)error << m_pWebSocket->errorString();
}

void WebSocketClient::connectUrl(QString url)
{
    m_url = url;
    m_pWebSocket->open(m_url);
}

void WebSocketClient::close()
{
    m_pWebSocket->close();
}

void WebSocketClient::sendTextMsg(const QString &message)
{
    if (!m_bConnected) {
        qDebug() << "webSocket not connect...";

        return;
    }

    m_pWebSocket->sendTextMessage(message);
}

void WebSocketClient::sendBinaryMsg(const QByteArray &data)
{
    if (!m_bConnected) {
        qDebug() << "webSocket not connect";

        return;
    }

    m_pWebSocket->sendBinaryMessage(data);
}

bool WebSocketClient::serverConnectStatus()
{
    return m_bConnected;
}

void WebSocketClient::reConnect()
{
    qDebug() << "webSocket reConnect";

    m_pWebSocket->abort();
    m_pWebSocket->open(m_url);
}

void WebSocketClient::init_socket_connect()
{
    m_pWebSocket = new QWebSocket();

    connect(m_pWebSocket, &QWebSocket::connected, this, &WebSocketClient::socketConnected);
    connect(m_pWebSocket, &QWebSocket::disconnected, this, &WebSocketClient::disSocketConnected);
    //connect(m_pWebSocket, &QWebSocket::error, this, &WebSocketClient::socketError);
}

