#ifndef CARDLABELEDITCARDS_H
#define CARDLABELEDITCARDS_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QFont>
#include <QMouseEvent>
#include <QPaintEvent>
#include "cards/card.h"

class CardLabelEditCards : public QLabel
{
    Q_OBJECT
public:
    explicit CardLabelEditCards(Card *card_, QWidget *parent = nullptr);

    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent*);

signals:
    void bepressed(Card *card);
    void behovered(Card *card);

private:
    int num;
    Card *card;
    int index;
    static QString digit[10];
};

#endif // CARDLABELEDITCARDS_H
