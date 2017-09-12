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
#include "cards/card.h"
#include "battleinterface.h"

class gameClient;


class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(gameClient *client_, const QString &Alldata, QObject *parent = nullptr);
    ~Player();

    gameClient *client;

    QString get_name()const;
    int get_totalgames()const;
    int get_victorygames()const;
    int get_drawgames()const;
    int get_defeatgames()const;
    int get_nextdeckname();
    bool update_deck(QString name, Card* leader, QList<Card*> *cardlist);
    QList<Deck*>& get_decks();
    QList<Deck*>* get_decks_pointer();
    BattleInterface* get_battle();
    void set_battle(BattleInterface*);

signals:

public slots:
private:
    QString name;
    int totalgames, victorygames, drawgames, defeatgames;
    QList<Deck*> decks;
    int name_helper;
    BattleInterface *battle;
};

#endif // PLAYER_H
