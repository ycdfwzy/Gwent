#ifndef SHOWBATTLECARD_H
#define SHOWBATTLECARD_H

#include <QWidget>
#include <QList>
#include <QStringList>
#include <QMouseEvent>
#include "cards/card.h"
#include "cards/deck.h"
#include "cards/cardlabelinbattle.h"
#include "cards/placeholder.h"

class ShowBattleCard : public QWidget
{
    Q_OBJECT
public:
    explicit ShowBattleCard(QList<Card*> *cardlist, QWidget *parent = nullptr);
    explicit ShowBattleCard(QString info, QWidget *parent = nullptr);

    void addonecard(Card* card, int pos);
    void addonecard(int id, int pos);
    void deleteonecard(int pos);
    void deleteonecard(Card* card);

    //void resizeEvent(QResizeEvent*);
    void Resize(int, int);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);

signals:
    void send_press_card(int);
    void send_hover_card(int);
    void send_press_blank(int);

public slots:
    void receive_press_card(int);
    void receive_hover_card(int);
    void receive_press_blank(int);

private:
    QList<Card*> *cardlist;
    QList<CardLabelinBattle*> showlist;
    QList<PlaceHolder*> blanks;
};

#endif // SHOWBATTLECARD_H
