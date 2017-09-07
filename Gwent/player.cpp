#include "player.h"
#include "gameclient.h"
#include <QDebug>

Player::Player(gameClient *client_, const QString &Alldata, QObject *parent) : QObject(parent){
    client = client_;

    QJsonParseError error;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(Alldata.toUtf8(), &error);
    if (error.error == QJsonParseError::NoError){
        if (!(jsonDocument.isNull() || jsonDocument.isEmpty())){
            if (jsonDocument.isObject()){
                QJsonObject info = jsonDocument.object();

                name = info.take("name").toVariant().toString();
                totalgames = info.take("totalgames").toVariant().toInt();
                victorygames = info.take("victorygames").toVariant().toInt();
                drawgames = info.take("drawgames").toInt();
                defeatgames = info.take("defeatgames").toInt();

                //QJsonValue decksJsonValue = info.take("decks");
                QJsonObject decks_ = info.take("decks").toObject();
                Deck *dk;
                QStringList ks = decks_.keys();
                int sz = ks.size();
                for (int i = 0; i < sz; ++i){
                    QString tmp = ks.at(i);
                    dk = new Deck(tmp , decks_.value(tmp));
                    decks.append(dk);
                }
            }
        }
    }
    //qDebug() << "init player!";
    //qDebug() << name << totalgames << victorygames << drawgames << defeatgames;
}

Player::~Player(){}


QString Player::get_name()const{return name;}
int Player::get_totalgames()const{return totalgames;}
int Player::get_victorygames()const{return victorygames;}
int Player::get_drawgames()const{return drawgames;}
int Player::get_defeatgames()const{return defeatgames;}
QList<Deck*>& Player::get_decks(){return decks;}
QList<Deck*>* Player::get_decks_pointer(){return &decks;}
