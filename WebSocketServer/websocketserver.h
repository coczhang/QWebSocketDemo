#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>

class WebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketServer(QObject *parent = 0);
    ~WebSocketServer();

signals:
    void sigTextMessage(QString message);
    void sigDisconnected();

private slots:
    void onNewConnection();
    void onTextMessageReived(const QString &message);
    void onDisconnected();

private:
    void initSocketConnect();

public:
    void sendTextMessage(QString info);
    void closeWebServer();

private:
    QWebSocketServer *m_pWebSocketServer;
    QWebSocket *m_pWebSocket;
};

#endif
