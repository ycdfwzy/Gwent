#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QtGui>
#include <QString>
#include <QtNetwork/QTcpSocket>
#include "mytcpsocket.h"
#include "waitbattleinterface.h"

class MainWindow;

class gameClient : public QObject
{
    Q_OBJECT
public:
    gameClient(MainWindow *mw_);
    ~gameClient();

    void tryconnect();
    void Read_Data();
    void dealwithmsg(QString);
    void Send_Date(QString);
    void set_wbi(WaitBattleInterface*);
    MyTCPSocket *client;

signals:
    void foundsignal();

private:
    MainWindow *mw;
    WaitBattleInterface *wbi;
};

#endif // GAMECLIENT_H
