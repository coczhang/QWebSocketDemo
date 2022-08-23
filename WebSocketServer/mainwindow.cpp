#include "mainwindow.h"

#include <QDateTime>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initDialogLayout();
    initDialogConnect();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initDialogLayout()
{
    this->setWindowTitle("webServer服务端");
    this->setFixedSize(this->width(), this->height());

    m_pTextRead = new QTextEdit(this);
    m_pTextRead->setGeometry(10, 5, this->width() - 20, this->height() / 2 - 40);
    m_pTextRead->setReadOnly(true);

    m_pTextWrite = new QTextEdit(this);
    m_pTextWrite->setGeometry(10, this->height() / 2 - 30, this->width() - 20, this->height() / 2 - 40);

    m_pButtonSend = new QPushButton("Send", this);
    m_pButtonSend->setGeometry(10, this->height() - 50, 80, 30);

    m_pButtonClose = new QPushButton("Close", this);
    m_pButtonClose->setGeometry(this->width() - 90, this->height() - 50, 80, 30);
}

void MainWindow::initDialogConnect()
{
    m_pWebServer = new WebSocketServer();
    connect(m_pWebServer, &WebSocketServer::sigTextMessage, this, &MainWindow::slotsTextMessage);
    connect(m_pWebServer, &WebSocketServer::sigDisconnected, this, &MainWindow::slotsDisconnected);


    connect(m_pButtonSend, &QPushButton::clicked, this, &MainWindow::btnSendClicked);
    connect(m_pButtonClose, &QPushButton::clicked, this, &MainWindow::btnCloseClicked);
}

void MainWindow::btnSendClicked()
{
    //获取编辑框内容
    QString content = m_pTextWrite->toPlainText();
    if (content.isEmpty()) {
        QMessageBox::critical(this, "错误", "不能发送空消息!", QMessageBox::Ok);

        return;
    }
    QDateTime dataTime = QDateTime::currentDateTime();
    QString strTime = dataTime.toString("hh:mm:ss");
    QString strInfo = content + QString(" [%1]").arg(strTime);

    m_pWebServer->sendTextMessage(strInfo);

    m_pTextWrite->clear();
}

void MainWindow::btnCloseClicked()
{
    this->close();
    m_pWebServer->closeWebServer();
}

void MainWindow::slotsTextMessage(QString message)
{
    QString strInfo = "recv from client:" + message;

    m_pTextRead->append(strInfo);
}

void MainWindow::slotsDisconnected()
{
    QDateTime dataTime = QDateTime::currentDateTime();
    QString strTime = dataTime.toString("hh:mm:ss");
    QString strInfo = QString("webSocket disconnect [%1]").arg(strTime);

    m_pTextRead->append(strInfo);
}
