#ifndef CHOOSEFORBATTLEINTERFACE_H
#define CHOOSEFORBATTLEINTERFACE_H

#include <QWidget>
#include <QScrollArea>
#include "cards/showcardsalldecks.h"

class MainWindow;

class ChooseforBattleInterface : public QWidget
{
    Q_OBJECT
public:
    explicit ChooseforBattleInterface(MainWindow *mw_, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mouseMoveEvent(QMouseEvent *);
signals:

public slots:
    void dochoice(int id);

private:
    QScrollArea *deckwindow;
    QList<Deck*> *decklist;
    ShowCardsAllDecks *scad;
    MainWindow *mw;
};

#endif // CHOOSEFORBATTLEINTERFACE_H
