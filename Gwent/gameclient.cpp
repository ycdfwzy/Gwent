#include "gameclient.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QEventLoop>
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

    qDebug() << str;

    QStringList strlist = str.split(';');
    int sz = strlist.size();
    for (int i = 0; i < sz-1; ++i){
        dealwithmsg(QString(strlist.at(i)));
    }

}

void gameClient::set_wbi(WaitBattleInterface* wbi_){
    wbi = wbi_;
}

void gameClient::dealwithmsg(QString str){
    qDebug() << str;
    if (str.compare("Sorry!") == 0){
        QMessageBox::critical(mw, QObject::tr("Error"), QObject::tr("Please check your ID and password, then try agian!"));
        return;
    } else
    if (str.startsWith("Welcome!")){
        mw->switchstate(MainWindow::Home);
        /*if (str.startsWith("Welcome!Data:")){
            str = str.mid(13);
            mw->init_player(str);
        }*/
    } else
    if (str.startsWith("Data:")){
        str = str.mid(5);
        mw->init_player(str);
    } else
    if (str.startsWith("FOUND ")){
        /*emit foundsignal();
        QEventLoop eventloop;
        QTimer::singleShot(1000, &eventloop, SLOT(quit()));
        eventloop.exec();*/
        wbi->hasfound();
    } else
    if (mw->get_player()->get_battle() != nullptr){
    if (str.startsWith("LoadDeck: ")){
        QString str0 = str.mid(10);
        if (str0.startsWith('0'))
            mw->get_player()->get_battle()->loaddeck(0, str0.mid(2));
        else
            mw->get_player()->get_battle()->loaddeck(1, str0.mid(2));
        /*
        if (str.startsWith("LoadDeck_m: ")){
            QString str0 = str.mid(12);
            mw->get_player()->get_battle()->loaddeck_m(str0);
        } else
        {
            QString str0 = str.mid(12);
            mw->get_player()->get_battle()->loaddeck_o(str0);
        }
        */
    } else
    if (str.startsWith("PUMP: ")){
        QString str0 = str.mid(6);
        int t;
        if (str0.startsWith('0')) t = 0;
        else t = 1;
        str0 = str0.mid(2);
        mw->get_player()->get_battle()->pump(t, str0.toInt());
        /*
        if (str.startsWith("PUMP_m: ")){
            QString str0 = str.mid(8);
            mw->get_player()->get_battle()->pump_m(str0.toInt());
        } else
        {
            QString str0 = str.mid(8);
            mw->get_player()->get_battle()->pump_o(str0.toInt());
        }
        */
    } else
    if (str.startsWith("Mulligan")){//提示调度
        QString str0 = str.mid(8);
        mw->get_player()->get_battle()->Mulligantips(str0.toInt());
    } else
    if (str.startsWith("Round")){//提示下一轮
        QString str0 = str.mid(5);
        mw->get_player()->get_battle()->roundstarttips(str0.toInt());
    } else
    if (str.startsWith("turn")){//提示回合
        if (str.startsWith("turn_m!")){
            mw->get_player()->get_battle()->turntip(0);
        } else {
            mw->get_player()->get_battle()->turntip(1);
        }
    } else
    if (str.startsWith("winthisround")){//提示赢一轮
        mw->get_player()->get_battle()->roundendtips(0);
    } else
    if (str.startsWith("losethisround")){//提示输一轮
        mw->get_player()->get_battle()->roundendtips(1);
    } else
    if (str.startsWith("drawthisround")){//提示平局
        mw->get_player()->get_battle()->roundendtips(2);
    } else
    if (str.startsWith("move ")){//卡牌移动
        QString str0 = str.mid(5);
        mw->get_player()->get_battle()->move(str0);
    } else
    if (str.startsWith("YOUGETDRAW!")){//平局
        mw->get_player()->get_battle()->gameover(2);
    } else
    if (str.startsWith("YOUAREWINNER!")){//胜利
        mw->get_player()->get_battle()->gameover(0);
    } else
    if (str.startsWith("YOUAERLOSER!")){//失败
        mw->get_player()->get_battle()->gameover(1);
    } else
    if (str.startsWith("bloodchange ")){
        QString str0 = str.mid(12);
        mw->get_player()->get_battle()->bloodchange(str0);
    } else
    if (str.startsWith("sky ")){
        QString str0 = str.mid(4);
        mw->get_player()->get_battle()->set_sky(str0);
    }
    }
}

void gameClient::Send_Date(QString msg){
    msg = msg + ";";
    client->write(msg.toLatin1());
    //client->flush();
    client->waitForBytesWritten();
}
