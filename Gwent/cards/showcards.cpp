#include "showcards.h"
#include <QPushButton>
#include <QLayout>

ShowCards::ShowCards(QList<Card*> &cardslist, QWidget *parent) : QWidget(parent)
{
    foreach (Card* cd, cardslist) {
        CardLabel *tmp = new CardLabel(*cd, this);
        cl.append(tmp);
    }
}

void ShowCards::Resize(int w, int h){
    int sz = cl.size();
    this->resize(sz*h*50/71, h);
    for (int i = 0 ; i < sz; ++i){
        CardLabel *tmp = cl.at(i);
        tmp->setGeometry(i*(h*50/71), 0, h*50/71, h);
    }
}
