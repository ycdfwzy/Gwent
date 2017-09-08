#include "showcardsalldecks.h"
#include <QPushButton>
#include <QLayout>
#include <QDebug>

ShowCardsAllDecks::ShowCardsAllDecks(QList<Deck*> *cardslist, QWidget *parent) : QWidget(parent)
{
    /*foreach (Card* cd, cardslist) {
        CardLabel *tmp = new CardLabel(cd, this);
        cl.append(tmp);
    }*/
    this->setMouseTracking(true);
    int sz = cardslist->size();
    for (int i = 0; i < sz; ++i){
        Deck* tmp = cardslist->at(i);
        QString msg = tmp->get_name() + "(" + QString::number(tmp->get_cards().size()) + " cards)";
        CardLabelChooseDeck *x = new CardLabelChooseDeck(tmp->get_leader(), i, msg, this);
        cl.append(x);
        connect(x, SIGNAL(bepressed(int)), this, SLOT(somebepressed(int)));
    }

}

void ShowCardsAllDecks::Resize(int w, int h){
    int sz = cl.size();
    this->resize(sz*h*500/71/9, h);
    for (int i = 0 ; i < sz; ++i){
        CardLabelChooseDeck *tmp = cl.at(i);
        tmp->setGeometry(i*(h*500/71/9)+h*50/71/18, 0, (h*50/71), h);
    }
}

QList<CardLabelChooseDeck*>* ShowCardsAllDecks::getcontains(){return &cl;}

void ShowCardsAllDecks::mouseMoveEvent(QMouseEvent *){
    int sz = cl.size();
    for (int i = 0; i < sz; ++i){
        CardLabelChooseDeck* clcd = cl.at(i);
        if (clcd->get_showmsg()){
            clcd->change_showmsg();
            clcd->update();
        }
    }
}

void ShowCardsAllDecks::mousePressEvent(QMouseEvent *){

}

void ShowCardsAllDecks::somebepressed(int id){
    emit haschosen(id);
}
