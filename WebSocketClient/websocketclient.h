#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QObject>
#include <QWebSocket>
#include <QUrl>

class WebSocketClient : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketClient(QObject *parent = 0);
    ~WebSocketClient();

signals:
    void sigRecvTextMsg(QString message);      //接收到Text类型消息的信号
    void sigConnected();
    void sigDisconnected();

private slots:
    void socketConnected();
    void disSocketConnected();
    void socketRecvTextMsg(QString message);
    void socketRecvBinaryMsg(QByteArray message);
    void socketError(QAbstractSocket::SocketError error);

public:
    void connectUrl(QString url);               //连接webSocket
    void close();                               //关闭webSocket
    void sendTextMsg(const QString &message);   //发送文本类型的消息
    void sendBinaryMsg(const QByteArray &data); //发送Binary类型的消息
    bool serverConnectStatus();                 //返回服务端的连接状态

private:
    void reConnect();
    void init_socket_connect();

private:
    QWebSocket *m_pWebSocket;
    QUrl m_url;

    bool m_bConnected;
};

#endif
