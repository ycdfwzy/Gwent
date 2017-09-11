#include "cardlabelinbattle.h"

QString CardLabelinBattle::digit[10]={
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

CardLabelinBattle::CardLabelinBattle(Card *card_, int index, QWidget *parent) : QLabel(parent)
{
    this->card = card_;
    this->index = index;
    this->setMouseTracking(true);
}

void CardLabelinBattle::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(card->get_picpath()));
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/images/"+card->get_color()+"frame"));

    int blood = card->get_baseblood() + card->get_boostblood();
    if (blood > 0){
        if (blood < 10){
            painter.drawPixmap(5, 5, this->width()/5, this->height()/5, QPixmap(digit[blood]));
        } else
        if (blood < 100){
            painter.drawPixmap(5, 5, this->width()/15*2, this->height()/5, QPixmap(digit[blood/10]));
            painter.drawPixmap(5+this->width()/15, 5, this->width()/15*2, this->height()/5, QPixmap(digit[blood%10]));
        } else
        if (blood < 1000){
            painter.drawPixmap(5, 5, this->width()/10, this->height()/5, QPixmap(digit[blood/100]));
            painter.drawPixmap(5+this->width()/20, 5, this->width()/10, this->height()/5, QPixmap(digit[blood/10%10]));
            painter.drawPixmap(5+this->width()/10, 5, this->width()/10, this->height()/5, QPixmap(digit[blood%10]));
        }

        painter.drawPixmap(5, 5+this->height()/5, this->width()/5, this->height()/5, QPixmap(":/images/"+card->get_location()));

        int armor = card->get_armor();
        if (armor > 0){
            painter.drawPixmap(5, 5+this->height()*2/5, this->width()/5, this->height()/5, QPixmap(":/images/armor"));
            if (armor < 1000){
                if (blood < 10){
                    painter.drawPixmap(5, 5+this->height()*2/5, this->width()/5, this->height()/5, QPixmap(digit[blood]));
                } else
                if (blood < 100){
                    painter.drawPixmap(5, 5+this->height()*2/5, this->width()/15*2, this->height()/5, QPixmap(digit[blood/10]));
                    painter.drawPixmap(5+this->width()/15, 5+this->height()*2/5, this->width()/15*2, this->height()/5, QPixmap(digit[blood%10]));
                } else
                if (blood < 1000){
                    painter.drawPixmap(5, 5+this->height()*2/5, this->width()/10, this->height()/5, QPixmap(digit[blood/100]));
                    painter.drawPixmap(5+this->width()/20, 5+this->height()*2/5, this->width()/10, this->height()/5, QPixmap(digit[blood%100/10]));
                    painter.drawPixmap(5+this->width()/10, 5+this->height()*2/5, this->width()/10, this->height()/5, QPixmap(digit[blood%10]));
                }
            }
        }
    }

}

void CardLabelinBattle::mouseMoveEvent(QMouseEvent *){
    emit send_hover(index);
}

void CardLabelinBattle::mousePressEvent(QMouseEvent *){
    emit send_press(index);
}
