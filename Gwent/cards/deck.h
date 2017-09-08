#ifndef DECK_H
#define DECK_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>
#include <QList>
#include "cards/card.h"

class Deck : public QObject
{
    Q_OBJECT
public:
    explicit Deck(const QString &name_, QJsonValue &info, QObject *parent = nullptr);
    explicit Deck(const QString &name_, QString info, QObject *parent = nullptr);

    static Deck* get_ALL();

    QString get_name()const;
    Card* get_leader()const;
    QList<Card*>& get_cards();
    QList<Card*>* get_cards_pointer();

signals:

public slots:

private:
    QString name;
    Card *leader;
    QList<Card*> cards;
    static Deck *ALL;
};

#endif // DECK_H
