#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QVariantMap>
#include <QList>
#include "cards/deck.h"

class gameClient;

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(gameClient *client_, const QString &Alldata, QObject *parent = nullptr);
    ~Player();

    gameClient *client;

signals:

public slots:
private:
    QString name;
    int totalgames, victorygames, drawgames,defeatgames;
    QList<Deck*> decks;
};

#endif // PLAYER_H
