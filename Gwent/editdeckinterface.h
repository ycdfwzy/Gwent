#ifndef EDITDECKINTERFACE_H
#define EDITDECKINTERFACE_H

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QPainter>
#include <QList>
#include <QTextEdit>
#include "cards/showcardsalldecks.h"
#include "cards/card.h"
#include "cards/deck.h"
#include "cards/cardlabelchoosdeck.h"
#include "cards/showcardsindeck.h"
#include <QMouseEvent>

class MainWindow;

class EditDeckInterface : public QWidget
{
    Q_OBJECT
public:
    explicit EditDeckInterface(MainWindow *mw_, QWidget *parent = nullptr);

    MainWindow *mw;
    void Backtohome();
    void Toeditdecks();
    void Save_Exit();
    void Exit();

signals:

public slots:
    void ToCardState(int id);
    void unshowcard();
    void showcard(Card* card_);
    void addonecard(Card* card_);
    void removeonecard(Card* card_);

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseResleaseEvent(QMouseEvent *);

private:
    QScrollArea *deckwindow, *cardwindow_all, *cardwindow_deck;
    QList<Deck*> *decklist;
    ShowCardsAllDecks *scad;
    ShowCardsInDeck *scid_all, *scid_deck;
    QPushButton *btnback, *btnnew, *btnsave, *btnexit;
    QTextEdit *edt;
    int state;
    //static QString background[2];
};

#endif // EDITDECKINTERFACE_H
