#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

    //设置默认地址和端口
    ui->ip->setText("127.0.0.1");
    ui->port->setText(QString::number(9999)); // QString::number(9999)


    //创建监听套接字
    listen  = new QTcpServer(this);
    //设置监听
    listen->listen(QHostAddress(ui->ip->text()), ui->port->text().toInt());

    // 监听新链接
    connect(listen,&QTcpServer::newConnection,[=](){
        //Returns the next pending connection as a connected QTcpSocket object.
        conn = listen->nextPendingConnection(); // 沟通的桥梁  通信套接字

        ui->record->append("有新的连接了");

        // 保证conn对象有效,所以放到新连接这里
        // 接收数据
        connect(conn,&QTcpSocket::readyRead,[=](){
            QByteArray array = conn->readAll();
            ui->record->append(array);

        });


    });


    // 发送数据
    connect(ui->sendBtn,&QPushButton::clicked,[=](){
        QString msg = ui->msgEdit->toPlainText();

        conn->write(msg.toUtf8()); // 发送数据

        ui->record->append("my say:" + msg); // 将数据显示到记录框
        ui->msgEdit->clear(); //清空输入框
    });


}

Server::~Server()
{
    delete ui;
}

