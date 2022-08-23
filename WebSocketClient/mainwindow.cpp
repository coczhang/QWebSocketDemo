#include "mainwindow.h"

#include <QMessageBox>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    init_dialog_layout();
    init_dialog_connect();
}

MainWindow::~MainWindow()
{
    if (m_pWebClient != NULL) {
        delete m_pWebClient;
        m_pWebClient = NULL;
    }
}

void MainWindow::init_dialog_layout()
{
    this->setWindowTitle("webSocket客户端");
    this->setFixedSize(this->width(), this->height());

    m_pLabelIp = new QLabel("服务器IP：", this);
    m_pLabelIp->setGeometry(20, 12, 80, 30);

    m_pLineIp = new QLineEdit("127.0.0.1", this);
    m_pLineIp->setGeometry(120, 13, 400, 30);
    m_pLineIp->setDisabled(true);

    m_pLabelPort = new QLabel("服务器端口：", this);
    m_pLabelPort->setGeometry(20, 50, 82 ,30);

    m_pLinePort = new QLineEdit("8888", this);
    m_pLinePort->setGeometry(120, 50, 400, 30);
    m_pLinePort->setDisabled(true);

    m_pButtonConnect = new QPushButton("Connect", this);
    m_pButtonConnect->setGeometry(540, 35, 80, 30);

    m_pTextRead = new QTextEdit(this);
    m_pTextRead->setGeometry(20, 100, 600, 150);
    m_pTextRead->setReadOnly(true);

    m_pTextWrite = new QTextEdit(this);
    m_pTextWrite->setGeometry(20, 260, 600, 150);

    m_pButtonSend = new QPushButton("Send", this);
    m_pButtonSend->setGeometry(10, this->height() - 40, 80, 30);

    m_pButtonClose = new QPushButton("Close", this);
    m_pButtonClose->setGeometry(this->width()- 90, this->height() - 40, 80, 30);
}

void MainWindow::init_dialog_connect()
{
    m_pWebClient = new WebSocketClient();

    connect(m_pButtonConnect, &QPushButton::clicked, this, &MainWindow::btnConnectClicked);
    connect(m_pButtonSend, &QPushButton::clicked, this, &MainWindow::btnSendClicked);
    connect(m_pButtonClose, &QPushButton::clicked, this, &MainWindow::btnCloseClicked);

    connect(m_pWebClient, &WebSocketClient::sigRecvTextMsg, this, &MainWindow::slotsRecvTextMsg);
    connect(m_pWebClient, &WebSocketClient::sigConnected, this, &MainWindow::slotsConnected);
    connect(m_pWebClient, &WebSocketClient::sigDisconnected, this, &MainWindow::slotsDisconnected);
}

void MainWindow::btnConnectClicked()
{
    if (m_pWebClient->serverConnectStatus()) {
        QDateTime dataTime = QDateTime::currentDateTime();
        QString strTime = dataTime.toString("hh:mm:ss");
        QString strInfo = "server already connect" + QString("[%1]").arg(strTime);
        m_pTextRead->append(strInfo);

        return;
    }

    QString url = QString("ws://%1:%2").arg(m_pLineIp->text()).arg(m_pLinePort->text());
    m_pWebClient->connectUrl(url);

    m_pTextRead->append("url:" + url);
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
    QString strInfo = content + QString("[%1]").arg(strTime);
    m_pWebClient->sendTextMsg(strInfo);

    m_pTextWrite->clear();
}

void MainWindow::btnCloseClicked()
{
    this->close();
    m_pWebClient->close();
}

void MainWindow::slotsRecvTextMsg(QString message)
{


    QString strInfo = "recv from server:" + message;
    m_pTextRead->append(strInfo);
}

void MainWindow::slotsConnected()
{
    QDateTime dataTime = QDateTime::currentDateTime();
    QString strTime = dataTime.toString("hh:mm:ss");
    QString strInfo = "webSocket connect success..." + QString("[%1]").arg(strTime);
    m_pTextRead->append(strInfo);
}

void MainWindow::slotsDisconnected()
{
    QDateTime dataTime = QDateTime::currentDateTime();
    QString strTime = dataTime.toString("hh:mm:ss");
    QString strInfo = "webSocket disconnect..." + QString("[%1]").arg(strTime);
    m_pTextRead->append(strInfo);
}
