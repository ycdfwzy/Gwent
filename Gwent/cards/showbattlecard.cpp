#include "showbattlecard.h"
#include <QDebug>

ShowBattleCard::ShowBattleCard(QList<Card*> *cardlist, QWidget *parent) : QWidget(parent)
{
    this->setMouseTracking(true);

    if (cardlist == nullptr){
        this->cardlist = new QList<Card*>;
        this->cardlist->clear();
    } else this->cardlist = cardlist;
    // or do copy-constructor?

    int sz = this->cardlist->size();
    for (int i = 0; i < sz; ++i){
        Card* card = this->cardlist->at(i);
        CardLabelinBattle *tmp = new CardLabelinBattle(card, i, this);
        tmp->setVisible(true);
        showlist.append(tmp);
        connect(tmp, SIGNAL(send_press(int)), this, SLOT(receive_press_card(int)));
        connect(tmp, SIGNAL(send_hover(int)), this, SLOT(receive_hover_card(int)));
    }
}

ShowBattleCard::ShowBattleCard(QString info, QWidget *parent):QWidget(parent){
    this->setMouseTracking(true);

    cardlist = new QList<Card*>;
    cardlist->clear();
    QStringList strlist = info.split(" ");
    int sz = strlist.size();
    for (int i = 0; i < sz; ++i){
        QString st = strlist.at(i);
        Card *card = new Card(st.toInt());
        cardlist->append(card);
        CardLabelinBattle *tmp = new CardLabelinBattle(card, i, this);
        tmp->setVisible(true);
        showlist.append(tmp);
        connect(tmp, SIGNAL(send_press(int)), this, SLOT(receive_press_card(int)));
        connect(tmp, SIGNAL(send_hover(int)), this, SLOT(receive_hover_card(int)));
    }
    qDebug() << showlist.size();
}

void ShowBattleCard::Resize(int, int h){
    while (!blanks.empty()){
        PlaceHolder *blank = blanks.front();
        disconnect(blank, SIGNAL(send_pressed(int)), this, SLOT(receive_press_blank(int)));
        delete blank;
        blanks.pop_front();
    }

    int sz = showlist.size();
    this->resize(sz*h*500/71/9, h);
    for (int i = 0 ; i < sz; ++i){
        CardLabelinBattle *tmp = showlist.at(i);
        tmp->setGeometry(i*(h*500/71/9)+h*50/71/18, 0, (h*50/71), h);
        PlaceHolder *blank = new PlaceHolder(i, this);
        blank->setVisible(true);
        int w = i*(h*500/71/9)-h*50/71/18;
        if (w < 0) w = 0;
        blank->setGeometry(w, 0, h*50/71/9, h);
        connect(blank, SIGNAL(send_pressed(int)), this, SLOT(receive_press_blank(int)));
        blanks.push_back(blank);
    }
    if (sz > 0){
        PlaceHolder *blank = new PlaceHolder(sz, this);
        blank->setVisible(true);
        int w = sz*(h*500/71/9)-h*50/71/18;
        blank->setGeometry(w, 0, h*50/71/9, h);
        connect(blank, SIGNAL(send_pressed(int)), this, SLOT(receive_press_blank(int)));
        blanks.push_back(blank);
    }
}

void ShowBattleCard::mouseMoveEvent(QMouseEvent *){

}

void ShowBattleCard::mousePressEvent(QMouseEvent *){
    emit send_hover_card(showlist.size());
}

void ShowBattleCard::addonecard(Card *card, int pos){
    cardlist->insert(pos, card);
    CardLabelinBattle *tmp = new CardLabelinBattle(card, pos+1, this);
    tmp->setVisible(true);
    showlist.insert(pos, tmp);
    connect(tmp, SIGNAL(send_press(int)), this, SLOT(receive_press_card(int)));
    connect(tmp, SIGNAL(send_hover(int)), this, SLOT(receive_hover_card(int)));
}

void ShowBattleCard::addonecard(int id, int pos){
    Card* card = new Card(id);
    addonecard(card, pos);
}

void ShowBattleCard::deleteonecard(int pos){
    cardlist->removeAt(pos);
    CardLabelinBattle *tmp = showlist.at(pos);
    disconnect(tmp, SIGNAL(send_press(int)), this, SLOT(receive_press_card(int)));
    disconnect(tmp, SIGNAL(send_hover(int)), this, SLOT(receive_hover_card(int)));
    delete tmp;
    cardlist->removeAt(pos);
}

void ShowBattleCard::deleteonecard(Card *card){
    int ind = cardlist->indexOf(card);
    deleteonecard(ind);
    //cardlist->removeAll(card);
}

void ShowBattleCard::receive_hover_card(int index){ emit send_hover_card(index);}
void ShowBattleCard::receive_press_blank(int index){ emit send_press_blank(index);}
void ShowBattleCard::receive_press_card(int index){ emit send_press_card(index);}
