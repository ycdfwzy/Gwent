#include "showcardsindeck.h"

ShowCardsInDeck::ShowCardsInDeck(Deck* deck, QWidget* parent):QWidget(parent)
{
    this->setMouseTracking(true);
    name = deck->get_name();
    leader = new Card(deck->get_leader()->get_id());
    QList<Card*> *tmp = deck->get_cards_pointer();
    int sz = tmp->size();
    for (int i = 0; i < sz; ++i){
        Card *x = tmp->at(i);
        CardLabelEditCards *temp = new CardLabelEditCards(x);
        cl.append(temp);
        connect(temp, SIGNAL(bepressed(Card*)), this, SLOT(receive_click(Card*)));
        connect(temp, SIGNAL(behovered(Card*)), this, SLOT(receive_hover(Card*)));
    }
}

void ShowCardsInDeck::receive_click(Card* card_){
    emit send_click(card_);
}

void ShowCardsInDeck::receive_hover(Card* Card_){
    emit send_hover(Card_);
}

void ShowCardsInDeck::Resize(int w, int h){
    int sz = cl.size();
    this->resize(sz*h*500/71/9, h);
    for (int i = 0 ; i < sz; ++i){
        CardLabelEditCards *tmp = cl.at(i);
        tmp->setGeometry(i*(h*500/71/9)+h*50/71/18, 0, (h*50/71), h);
    }
}

void ShowCardsInDeck::mouseMoveEvent(QMouseEvent*){
    emit mouse_move_here();
}

void ShowCardsInDeck::addonecard(Card* card_){
    Card *x = new Card(card_->get_id());
    cards.append(x);
    CardLabelEditCards *tmp = new CardLabelEditCards(x);
    cl.append(tmp);
    connect(tmp, SIGNAL(bepressed(Card*)), this, SLOT(receive_click(Card*)));
    connect(tmp, SIGNAL(behovered(Card*)), this, SLOT(receive_hover(Card*)));
}

void ShowCardsInDeck::removecard(Card* card_){
    int sz = cards.size();
    for (int i = 0; i < sz; ++i)
    if (card_ == cards.at(i)){
        cards.removeAt(i);
        cl.removeAt(i);
        break;
    }
}
