#include "showcardsindeck.h"
#include <QDebug>

ShowCardsInDeck::ShowCardsInDeck(Deck* deck, QWidget* parent):QWidget(parent)
{
    this->setMouseTracking(true);
    name = deck->get_name();

    if (deck->get_leader() != nullptr)
        leader = new Card(deck->get_leader()->get_id());
    else leader = nullptr;

    QList<Card*> *tmp = deck->get_cards_pointer();
    int sz = tmp->size();
    for (int i = 0; i < sz; ++i){
        Card *x = new Card(tmp->at(i)->get_id());
        cards.append(x);
        CardLabelEditCards *temp = new CardLabelEditCards(x, this);
        cl.append(temp);
        connect(temp, SIGNAL(bepressed(Card*)), this, SLOT(receive_click(Card*)));
        connect(temp, SIGNAL(behovered(Card*)), this, SLOT(receive_hover(Card*)));
    }
}

ShowCardsInDeck::ShowCardsInDeck(QWidget* parent):QWidget(parent){
    this->setMouseTracking(true);
    leader = nullptr;
    cards.clear();
    cl.clear();
}

void ShowCardsInDeck::changeDeck(Deck *deck){
    name = deck->get_name();

    if (leader != nullptr) delete leader;
    if (deck->get_leader() != nullptr)
        leader = new Card(deck->get_leader()->get_id());
    else
        leader = nullptr;

    int sz = cl.size();
    for (int i = 0; i < sz; ++i){
        CardLabelEditCards *temp = cl.at(i);
        disconnect(temp, SIGNAL(bepressed(Card*)), this, SLOT(receive_click(Card*)));
        disconnect(temp, SIGNAL(behovered(Card*)), this, SLOT(receive_hover(Card*)));

    }
    cards.clear();
    cl.clear();

    QList<Card*> *tmp = deck->get_cards_pointer();
    sz = tmp->size();
    for (int i = 0; i < sz; ++i){
        Card *x = new Card(tmp->at(i)->get_id());
        cards.append(x);
        CardLabelEditCards *temp = new CardLabelEditCards(x, this);
        cl.append(temp);
        temp->setVisible(true);
        connect(temp, SIGNAL(bepressed(Card*)), this, SLOT(receive_click(Card*)));
        connect(temp, SIGNAL(behovered(Card*)), this, SLOT(receive_hover(Card*)));
    }
}

void ShowCardsInDeck::receive_click(Card* card_){
    emit send_click(card_);
}

void ShowCardsInDeck::receive_hover(Card* Card_){
    //qDebug() << "hover";
    emit send_hover(Card_);
}

void ShowCardsInDeck::Resize(int w, int h){
    int sz = cl.size();
    this->resize(sz*h*500/71/9, h);
    for (int i = 0 ; i < sz; ++i){
        CardLabelEditCards *tmp = cl.at(i);
        tmp->setVisible(false);
        tmp->setGeometry(i*(h*500/71/9)+h*50/71/18, 0, (h*50/71), h);
        tmp->setVisible(true);
    }
}

void ShowCardsInDeck::mouseMoveEvent(QMouseEvent*){
    emit mouse_move_here();
}

void ShowCardsInDeck::addonecard(Card* card_){
    Card *x = new Card(card_->get_id());
    cards.append(x);
    CardLabelEditCards *tmp = new CardLabelEditCards(x, this);
    cl.append(tmp);
    tmp->setVisible(true);
    connect(tmp, SIGNAL(bepressed(Card*)), this, SLOT(receive_click(Card*)));
    connect(tmp, SIGNAL(behovered(Card*)), this, SLOT(receive_hover(Card*)));
}

void ShowCardsInDeck::removecard(Card* card_){
    int sz = cards.size();
    //qDebug() << sz;
    for (int i = 0; i < sz; ++i)
    if (card_ == cards.at(i)){
        //qDebug() << "find";
        CardLabelEditCards *tmp = cl.at(i);
        cards.removeAt(i);
        cl.removeAt(i);
        delete tmp;
        break;
    }
}

QList<Card *> *ShowCardsInDeck::get_cardlist(){return &cards;}
QString ShowCardsInDeck::get_name(){return name;}
Card* ShowCardsInDeck::get_leader(){return leader;}
