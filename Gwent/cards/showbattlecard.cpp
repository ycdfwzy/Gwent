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

ShowBattleCard::ShowBattleCard(QWidget *parent):QWidget(parent){
    this->setMouseTracking(true);
    cardlist = new QList<Card*>;
    cardlist->clear();
    showlist.clear();
}

void ShowBattleCard::loadcards(QString info){
    qDebug() << "loadcards " << info;
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
}

void ShowBattleCard::Resize(int w, int h){
    while (!blanks.empty()){
        PlaceHolder *blank = blanks.front();
        blank->setVisible(false);
        disconnect(blank, SIGNAL(send_pressed(int)), this, SLOT(receive_press_blank(int)));
        delete blank;
        blanks.pop_front();
    }

    int sz = showlist.size();
    int maxwidth;
    if (w > (sz+1)*h*500/71/9)
        maxwidth = w;
    else maxwidth = (sz+1)*h*500/71/9;
    this->resize(maxwidth, h);
    for (int i = 0 ; i < sz; ++i){
        CardLabelinBattle *tmp = showlist.at(i);
        tmp->set_index(i);
        tmp->setGeometry(i*(h*500/71/9)+h*50/71/18, 0, (h*50/71), h);
        PlaceHolder *blank = new PlaceHolder(i, this);
        blank->setVisible(true);
        int t = i*(h*500/71/9)-h*50/71/18;
        if (t < 0) t = 0;
        blank->setGeometry(t, 0, h*50/71/9, h);
        connect(blank, SIGNAL(send_pressed(int)), this, SLOT(receive_press_blank(int)));
        blanks.push_back(blank);
    }
    //if (sz > 0){
        PlaceHolder *blank = new PlaceHolder(sz, this);
        blank->setVisible(true);
        int t = sz*(h*500/71/9)-h*50/71/18;
        if ( t < 0) t = 0;
        //blank->setGeometry(w, 0, h*50/71/9, h);
        blank->setGeometry(t, 0, maxwidth-t, h);
        connect(blank, SIGNAL(send_pressed(int)), this, SLOT(receive_press_blank(int)));
        blanks.push_back(blank);
    //}
}

void ShowBattleCard::mouseMoveEvent(QMouseEvent *){
    //emit send_press_blank();
    qDebug() << "ShowBattleCard::mouseMoveEvent";
}

void ShowBattleCard::mousePressEvent(QMouseEvent *){
    qDebug() << "ShowBattleCard::mousePressEvent";
    emit send_press_blank(showlist.size());
}

void ShowBattleCard::addonecard(Card *card, int pos){
    qDebug() << "addonecard";
    cardlist->insert(pos, card);
    CardLabelinBattle *tmp = new CardLabelinBattle(card, pos+1, this);
    tmp->setVisible(true);
    showlist.insert(pos, tmp);
    connect(tmp, SIGNAL(send_press(int)), this, SLOT(receive_press_card(int)));
    connect(tmp, SIGNAL(send_hover(int)), this, SLOT(receive_hover_card(int)));
}

void ShowBattleCard::addonecard(int id, int pos){
    qDebug() << "addonecard";
    Card* card = new Card(id);
    addonecard(card, pos);
}

void ShowBattleCard::deleteonecard(int pos){
    qDebug() << "deleteonecard";
    cardlist->removeAt(pos);
    CardLabelinBattle *tmp = showlist.at(pos);
    disconnect(tmp, SIGNAL(send_press(int)), this, SLOT(receive_press_card(int)));
    disconnect(tmp, SIGNAL(send_hover(int)), this, SLOT(receive_hover_card(int)));
    delete tmp;
    showlist.removeAt(pos);
}

void ShowBattleCard::deleteonecard(Card *card){
    qDebug() << "deleteonecard";
    int ind = cardlist->indexOf(card);
    deleteonecard(ind);
    //cardlist->removeAll(card);
}

int ShowBattleCard::get_score(){
    int score = 0;
    foreach (Card* card, *cardlist) {
        score += card->get_baseblood()+card->get_boostblood();
    }
    return score;
}

void ShowBattleCard::receive_hover_card(int index){ emit send_hover_card(index);}
void ShowBattleCard::receive_press_blank(int index){ emit send_press_blank(index);}
void ShowBattleCard::receive_press_card(int index){ emit send_press_card(index);}
QList<Card*>* ShowBattleCard::get_cardlist(){return cardlist;}
