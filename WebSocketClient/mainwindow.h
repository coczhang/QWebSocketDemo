#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

#include "websocketclient.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void btnConnectClicked();
    void btnSendClicked();
    void btnCloseClicked();

    void slotsRecvTextMsg(QString message);
    void slotsConnected();
    void slotsDisconnected();

private:
    void init_dialog_layout();
    void init_dialog_connect();

private:
    QLabel*       m_pLabelIp;
    QLabel*       m_pLabelPort;

    QLineEdit*    m_pLineIp;
    QLineEdit*    m_pLinePort;

    QPushButton*  m_pButtonConnect;
    QPushButton*  m_pButtonSend;
    QPushButton*  m_pButtonClose;

    QTextEdit*    m_pTextRead;
    QTextEdit*    m_pTextWrite;

    WebSocketClient *m_pWebClient;
};

#endif
