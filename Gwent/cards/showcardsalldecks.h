#ifndef SHOWCARDS_H
#define SHOWCARDS_H

#include <QWidget>
#include "cards/cardlabelchoosdeck.h"
#include "cards/deck.h"
#include "cards/card.h"
#include <QList>
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>

class ShowCardsAllDecks : public QWidget
{
    Q_OBJECT
public:
    explicit ShowCardsAllDecks(QList<Deck*> *deckslist, QWidget *parent = nullptr);

    void update_deckslist(QList<Deck*> *deckslist);
    void Resize(int w, int h);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

    QList<CardLabelChooseDeck*>* getcontains();
signals:
    void haschosen(int id);

public slots:
    void somebepressed(int id);
private:
    QList<CardLabelChooseDeck*> cl;
};

#endif // SHOWCARDS_H
