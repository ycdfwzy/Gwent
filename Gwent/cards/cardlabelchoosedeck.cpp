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
