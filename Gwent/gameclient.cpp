#include "gameclient.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>

gameClient::gameClient(MainWindow *mw_){
    mw = mw_;
    client = new MyTCPSocket();
    client->connectToHost("192.168.13.1", 8888);
    if(!client->waitForConnected(30000)){
        QMessageBox::critical(mw, QObject::tr("Connection Error"), QObject::tr("Server not found!"));
        return;
    }
    //client->write();
    QObject::connect(client, &MyTCPSocket::readyReadClient, this, &gameClient::Read_Data);
}

gameClient::~gameClient(){}

void gameClient::Read_Data(){
    QByteArray buffer = client->readAll();
    QString str = buffer;
    if (str.compare("Sorry!") == 0){
        QMessageBox::critical(mw, QObject::tr("Error"), QObject::tr("Please check your ID and password, then try agian!"));
        return;
    } else
    if (str.compare("Welcome!") == 0){
        mw->switchstate(MainWindow::Home);
    }

    //qDebug() << str;
}

void gameClient::Send_Date(QString msg){
    client->write(msg.toLatin1());
}
