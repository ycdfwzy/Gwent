#ifndef CARDLABEL_H
#define CARDLABEL_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QFont>
#include <QMouseEvent>
#include <QPaintEvent>
#include "cards/card.h"

class CardLabelChooseDeck : public QLabel
{
    Q_OBJECT
public:
    CardLabelChooseDeck(Card *card, int index_, QString msg_, QWidget *parent = nullptr);

    bool get_showmsg();
    void change_showmsg();

    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

signals:
    void bepressed(int id);

private:
    bool showmsg;
    Card *card;
    int index;
    QString msg;
    static QString digit[10];
};

#endif // CARDLABEL_H
