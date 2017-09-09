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
}
