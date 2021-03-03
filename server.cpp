#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

    //设置默认地址和端口
    ui->ip->setText("127.0.0.1");
    ui->port->setText("9999"); // QString::number(9999)


    //创建监听套接字
    listen  = new QTcpServer(this);
    //设置监听
    listen->listen(QHostAddress(ui->ip->text()), ui->port->text().toInt());

    connect(listen,&QTcpServer::newConnection,[=](){
        //Returns the next pending connection as a connected QTcpSocket object.
        conn = listen->nextPendingConnection(); // 沟通的桥梁  通信套接字

//        conn->write();


    });




}

Server::~Server()
{
    delete ui;
}

