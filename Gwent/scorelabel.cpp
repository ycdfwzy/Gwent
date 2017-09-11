#include "scorelabel.h"
#include <QDebug>

QString ScoreLabel::digit[10]={
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

ScoreLabel::ScoreLabel(int score_, QWidget *parent) : QLabel(parent)
{
    score = score_;
}

void ScoreLabel::paintEvent(QPaintEvent *){
    QPainter painter(this);
    if (score < 10){
        painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(digit[score]));
    } else
    if (score < 100){
        painter.drawPixmap(0, 0, this->width()*2/3, this->height(), QPixmap(digit[score/10]));
        painter.drawPixmap(this->width()/3, 0, this->width()*2/3, this->height(), QPixmap(digit[score%10]));
    } else
    if (score < 1000){
        painter.drawPixmap(0, 0, this->width()/2, this->height(), QPixmap(digit[score/100]));
        painter.drawPixmap(this->width()/4, 0, this->width()/2, this->height(), QPixmap(digit[score%100/10]));
        painter.drawPixmap(this->width()/2, 0, this->width()/2, this->height(), QPixmap(digit[score%10]));
    }
}

int ScoreLabel::get_score(){return score;}
void ScoreLabel::set_score(int x){score = x;}
