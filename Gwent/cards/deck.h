#ifndef DECK_H
#define DECK_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include "cards/card.h"

class Deck : public QObject
{
    Q_OBJECT
public:
    explicit Deck(const QString &name_, QJsonValue &info, QObject *parent = nullptr);

    QString get_name()const;
    Card* get_leader()const;
    QList<Card*>& get_cards();
signals:

public slots:

private:
    QString name;
    Card *leader;
    QList<Card*> cards;
};

#endif // DECK_H
