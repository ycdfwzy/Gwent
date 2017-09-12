#ifndef CARDLABELINBATTLE_H
#define CARDLABELINBATTLE_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QFont>
#include <QMouseEvent>
#include <QPaintEvent>
#include "cards/card.h"

class CardLabelinBattle : public QLabel
{
    Q_OBJECT
public:
    CardLabelinBattle(Card* card_, int index, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void set_index(int);

signals:
    void send_hover(int index);
    void send_press(int index);

public slots:

private:
    Card *card;
    int index;
    static QString digit[10];
};

#endif // CARDLABELINBATTLE_H
