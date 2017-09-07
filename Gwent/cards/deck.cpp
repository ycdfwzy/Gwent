#include "deck.h"
#include <QDebug>

Deck::Deck(const QString &name_, QJsonValue &info, QObject *parent) : QObject(parent)
{
    //qWarning() << "Deck";
    //qWarning() << info;
    name = name_;
    if (info.isObject()){
        QJsonObject inf = info.toObject();
        leader = new Card(inf.take("leader").toVariant().toInt());
        QJsonArray cards_ = inf.take("cards").toArray();
        int sz = cards_.size();
        for (int i = 0; i < sz; ++i){
            QJsonValue x = cards_.at(i);
            cards.append(new Card(x.toInt()));
        }
    }
}

QString Deck::get_name()const{return name;}
Card* Deck::get_leader()const{return leader;}
QList<Card*>& Deck::get_cards(){return cards;}
