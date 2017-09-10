#include "cardlabeleditcards.h"
#include <QDebug>

QString CardLabelEditCards::digit[10]={
    ":/images/digit0",
    ":/images/digit1",
    ":/images/digit2",
    ":/images/digit3",
    ":/images/digit4",
    ":/images/digit5",
    ":/images/digit6",
    ":/images/digit7",
    ":/images/digit8",
    ":/images/digit9",
};

CardLabelEditCards::CardLabelEditCards(Card *card_, QWidget *parent):card(card_), QLabel(parent)
{
    this->setMouseTracking(true);
}


void CardLabelEditCards::mouseMoveEvent(QMouseEvent *){
    //qDebug() << "hover";
    emit behovered(card);
}

void CardLabelEditCards::mousePressEvent(QMouseEvent *){
    emit bepressed(card);
}

void CardLabelEditCards::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(card->get_picpath()));
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/images/"+card->get_color()+"frame"));

    if (card->get_baseblood() > 0){
        int blood = card->get_baseblood();
        if (blood < 10){
            painter.drawPixmap(5, 5, this->width()/5, this->height()/5, QPixmap(digit[blood]));
        } else
        if (blood < 100){
            painter.drawPixmap(5, 5, this->width()/15*2, this->height()/5, QPixmap(digit[blood/10]));
            painter.drawPixmap(5+this->width()/15, 5, this->width()/15*2, this->height()/5, QPixmap(digit[blood%10]));
        } else
        if (blood < 1000){
            painter.drawPixmap(5, 5, this->width()/10, this->height()/5, QPixmap(digit[blood/100]));
            painter.drawPixmap(5+this->width()/20, 5, this->width()/10, this->height()/5, QPixmap(digit[blood%100/10]));
            painter.drawPixmap(5+this->width()/10, 5, this->width()/10, this->height()/5, QPixmap(digit[blood%10]));
        }

        //qDebug() << ":/images/"+card->get_location();
        painter.drawPixmap(5, 5+this->height()/5, this->width()/5, this->height()/5, QPixmap(":/images/"+card->get_location()));
    }

}
