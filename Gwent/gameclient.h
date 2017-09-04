#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QtGui>
#include <QString>
#include <QtNetwork/QTcpSocket>
#include "mytcpsocket.h"

class MainWindow;

class gameClient : public QObject
{
    Q_OBJECT
public:
    gameClient(MainWindow *mw_);
    ~gameClient();

    void Read_Data();
    void Send_Date(QString);
    MyTCPSocket *client;

private:

    MainWindow *mw;
};

#endif // GAMECLIENT_H
