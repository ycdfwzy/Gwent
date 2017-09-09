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

    name_helper = 0;
    //qDebug() << "init player!";
    //qDebug() << name << totalgames << victorygames << drawgames << defeatgames;
}

Player::~Player(){}

bool Player::update_deck(QString name, Card* leader, QList<Card*> *cardlist){
    //send to server
    QString str = name + " " + QString::number(leader->get_id());
    foreach (Card* x, *cardlist){
        str += " " + QString::number(x->get_id());
    }
    str = "AddDeck: " + str;
    client->Send_Date(str);

    qDebug() << str;

    bool flag = false;
    int sz = decks.size();
    for (int i = 0; i < sz; ++i)
    if (name.compare(decks.at(i)->get_name()) == 0){
        flag = true;
        decks.at(i)->change_cardlist(cardlist);
        break;
    }
    if (!flag){
        Deck *tmp = new Deck(name, leader, cardlist);
        decks.append(tmp);
        name_helper++;
    }
    return flag;
}

QString Player::get_name()const{return name;}
int Player::get_totalgames()const{return totalgames;}
int Player::get_victorygames()const{return victorygames;}
int Player::get_drawgames()const{return drawgames;}
int Player::get_defeatgames()const{return defeatgames;}
QList<Deck*>& Player::get_decks(){return decks;}
QList<Deck*>* Player::get_decks_pointer(){return &decks;}
int Player::get_nextdeckname(){return name_helper+1;}
