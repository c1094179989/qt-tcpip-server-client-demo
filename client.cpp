#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

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

}

Client::~Client()
{
    delete ui;
}
