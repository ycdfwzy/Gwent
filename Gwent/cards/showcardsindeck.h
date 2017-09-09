#ifndef SHOWCARDSINDECK_H
#define SHOWCARDSINDECK_H

#include <QWidget>
#include <QList>
#include <QMouseEvent>
#include "cards/card.h"
#include "cards/deck.h"
#include "cards/cardlabeleditcards.h"

class ShowCardsInDeck : public QWidget
{
    Q_OBJECT
public:
    ShowCardsInDeck(Deck* deck, QWidget* parent = nullptr);
    ShowCardsInDeck(QWidget* parent = nullptr);

    void changeDeck(Deck* deck);
    void Resize(int w, int h);
    void mouseMoveEvent(QMouseEvent*);
    void addonecard(Card* card_);
    void removecard(Card* card_);
    QList<Card*>* get_cardlist();
    QString get_name();
    Card* get_leader();

signals:
    void send_click(Card* card_);
    void send_hover(Card* card_);
    void mouse_move_here();

public slots:
    void receive_click(Card* card_);
    void receive_hover(Card* Card_);

private:
    QString name;
    Card *leader;
    QList<Card*> cards;
    QList<CardLabelEditCards*> cl;
};

#endif // SHOWCARDSINDECK_H
