#include "cardlabel.h"
#include <QDebug>

QPixmap* CardLabel::digit[10]={nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};

CardLabel::CardLabel(Card &card_, QWidget *parent) :
   card(card_), QLabel(parent)
{
    if (digit[0] == nullptr){
        digit[0] = new QPixmap(":/images/digit0");
        digit[1] = new QPixmap(":/images/digit1");
        digit[2] = new QPixmap(":/images/digit2");
        digit[3] = new QPixmap(":/images/digit3");
        digit[4] = new QPixmap(":/images/digit4");
        digit[5] = new QPixmap(":/images/digit5");
        digit[6] = new QPixmap(":/images/digit6");
        digit[7] = new QPixmap(":/images/digit7");
        digit[8] = new QPixmap(":/images/digit8");
        digit[9] = new QPixmap(":/images/digit9");
    }

    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(card.get_picpath()));
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/images/"+card.get_color()+"frame"));
    //this->show();
    this->setMouseTracking(true);
}

void CardLabel::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(card.get_picpath()));
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/images/"+card.get_color()+"frame"));
}

void CardLabel::mouseMoveEvent(){

}

void CardLabel::mousePressEvent(QMouseEvent *){

}
