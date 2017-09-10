#include "gameclient.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>

gameClient::gameClient(MainWindow *mw_){
    mw = mw_;
    client = nullptr;
    tryconnect();
}

gameClient::~gameClient(){}

void gameClient::tryconnect(){
    if (client == nullptr) client = new MyTCPSocket();
    client->connectToHost("192.168.13.1", 8888);
    if(!client->waitForConnected(30000)){
        QMessageBox::critical(mw, QObject::tr("Connection Error"), QObject::tr("Server not found!"));
        delete client;
        client = nullptr;
        return;
    }
    QObject::connect(client, &MyTCPSocket::readyReadClient, this, &gameClient::Read_Data);
}

void gameClient::Read_Data(){
    QByteArray buffer = client->readAll();
    QString str = buffer;
    //qDebug() << str;
    if (str.compare("Sorry!") == 0){
        QMessageBox::critical(mw, QObject::tr("Error"), QObject::tr("Please check your ID and password, then try agian!"));
        return;
    } else
    if (str.startsWith("Welcome!")){
        mw->switchstate(MainWindow::Home);
        if (str.startsWith("Welcome!Data:")){
            str = str.mid(13);
            mw->init_player(str);
        }
    } else
    if (str.startsWith("Data:")){
        str = str.mid(5);
        mw->init_player(str);
    }

    //qDebug() << str;
}

void gameClient::Send_Date(QString msg){
    client->write(msg.toLatin1());
    client->waitForBytesWritten();
}
