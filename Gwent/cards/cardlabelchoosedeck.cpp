#include "cardlabelchoosdeck.h"
#include <QDebug>

QString CardLabelChooseDeck::digit[10]={
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

CardLabelChooseDeck::CardLabelChooseDeck(Card *card_, int index_, QString msg_, QWidget *parent) :
   card(card_), index(index_), msg(msg_), QLabel(parent)
{
    showmsg = false;
    this->setMouseTracking(true);
}

void CardLabelChooseDeck::paintEvent(QPaintEvent *){
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

        painter.drawPixmap(5, 5+this->height()/5, this->width()/5, this->height()/5, QPixmap(":/images/"+card->get_location()));
    }

    if (showmsg){
        painter.setPen(Qt::white);
        QFont font;
        font.setFamily("Microsoft YaHei");
        font.setPointSize(20);
        font.setItalic(true);
        painter.setFont(font);
        painter.drawText(0, this->height()*9/10, this->width(), this->height()/10 , Qt::AlignCenter, msg);
    }
}

void CardLabelChooseDeck::mouseMoveEvent(QMouseEvent *){
    if (!showmsg){
        showmsg = true;
        this->update();
    }
}

void CardLabelChooseDeck::mousePressEvent(QMouseEvent *){

}

void CardLabelChooseDeck::mouseReleaseEvent(QMouseEvent *){
    emit bepressed(index);
}

void CardLabelChooseDeck::change_showmsg(){ showmsg = !showmsg; }
bool CardLabelChooseDeck::get_showmsg(){return showmsg;}
