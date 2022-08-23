#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>

#include "websocketserver.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initDialogLayout();
    void initDialogConnect();

private slots:
    void btnSendClicked();
    void btnCloseClicked();

    void slotsTextMessage(QString message);
    void slotsDisconnected();

private:
    QTextEdit*     m_pTextRead;
    QTextEdit*     m_pTextWrite;

    QPushButton*   m_pButtonSend;
    QPushButton*   m_pButtonClose;

    WebSocketServer *m_pWebServer;
};

#endif
