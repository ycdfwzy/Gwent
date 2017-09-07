#ifndef CARDLABEL_H
#define CARDLABEL_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>
#include "cards/card.h"

class CardLabel : public QLabel
{
    Q_OBJECT
public:
    CardLabel(Card &card, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*);
    void mouseMoveEvent();
    void mousePressEvent(QMouseEvent *);

private:
    Card &card;
    static QPixmap *digit[10];
};

#endif // CARDLABEL_H
