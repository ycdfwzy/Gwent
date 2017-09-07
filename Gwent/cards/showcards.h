#ifndef SHOWCARDS_H
#define SHOWCARDS_H

#include <QWidget>
#include "cards/cardlabel.h"
#include "cards/card.h"
#include <QList>
#include <QPixmap>
#include <QLabel>

class ShowCards : public QWidget
{
    Q_OBJECT
public:
    explicit ShowCards(QList<Card*> &cardslist, QWidget *parent = nullptr);

    void Resize(int w, int h);
signals:

public slots:

private:
    QList<CardLabel*> cl;
};

#endif // SHOWCARDS_H
