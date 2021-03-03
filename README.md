# QT TCPIP socket 服务端 客户端通信演示





##服务端 Server



成员变量定义

~~~h
public:
    QTcpServer * listen;
    QTcpSocket * conn;
~~~



服务端实现 server.cpp :

~~~cpp
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

~~~





##客户端 Client



成员变量定义 

```h
public:
    QTcpSocket *client;
```

客户端实现:
~~~cpp
 //设置默认地址和端口
    ui->ip->setText("127.0.0.1");
    ui->port->setText(QString::number(9999)); // QString::number(9999)

    client = new QTcpSocket(this);

    //连接服务器
    client->connectToHost(ui->ip->text(),ui->port->text().toInt());

    connect(ui->sendBtn,&QPushButton::clicked,[=](){
        QString msg = ui->msgEdit->toPlainText();

        client->write(msg.toUtf8());
        ui->record->append("my say:"+ msg);
        ui->msgEdit->clear();
    });

    //客户端接收数据
    connect(client,&QTcpSocket::readyRead,[=](){
        QByteArray array = client->readAll();
        ui->record->append(array);

    });

~~~



## 启动客户端和服务端 main

~~~cpp
#include "server.h"
#include "client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server w;
    w.setWindowTitle("服务端");
    w.show();

    Client c;
    c.setWindowTitle("客户端");
    c.show();

    return a.exec();
}

~~~









