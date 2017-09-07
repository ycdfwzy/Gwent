#ifndef EDITDECKINTERFACE_H
#define EDITDECKINTERFACE_H

#include <QWidget>
#include <QScrollArea>
#include <QPainter>
#include <QList>
#include "cards/showcards.h"
#include "cards/card.h"
#include "cards/deck.h"

class MainWindow;

class EditDeckInterface : public QWidget
{
    Q_OBJECT
public:
    explicit EditDeckInterface(MainWindow *mw_, QWidget *parent = nullptr);

    MainWindow *mw;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

private:
    QScrollArea *deckwindow;
    QList<Deck*> *decklist;
    ShowCards *sc;
};

#endif // EDITDECKINTERFACE_H
