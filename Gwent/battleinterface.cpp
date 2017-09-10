#include "battleinterface.h"
#include "mainwindow.h"

BattleInterface::BattleInterface(MainWindow *mw_, QWidget *parent) : QWidget(parent)
{
    mw = mw_;
    this->setMouseTracking(true);

    m_graveyard = new QScrollArea(this);
    //m_graveyard->setStyleSheet("background-color:transparent");
    m_graveyard->setVisible(false);
    m_card = new QScrollArea(this);
    m_card->setStyleSheet("background-color:transparent");
    m_melee = new QScrollArea(this);
    m_melee->setStyleSheet("background-color:transparent");
    m_ranged = new QScrollArea(this);
    m_ranged->setStyleSheet("background-color:transparent");
    m_siege = new QScrollArea(this);
    m_siege->setStyleSheet("background-color:transparent");

    o_graveyard = new QScrollArea(this);
    //o_graveyard->setStyleSheet("background-color:transparent");
    o_graveyard->setVisible(false);
    o_card = new QScrollArea(this);
    o_card->setStyleSheet("background-color:transparent");
    o_melee = new QScrollArea(this);
    o_melee->setStyleSheet("background-color:transparent");
    o_ranged = new QScrollArea(this);
    o_ranged->setStyleSheet("background-color:transparent");
    o_siege = new QScrollArea(this);
    o_siege->setStyleSheet("background-color:transparent");
}

void BattleInterface::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/battleboard"));
}

void BattleInterface::resizeEvent(QResizeEvent *){
    m_card->setGeometry(this->width()*66/192, this->height()*97/108, this->width()*77/192, this->height()*11/108);
    m_melee->setGeometry(this->width()*70/192, this->height()*56/108, this->width()*51/192, this->height()*11/108);
    m_ranged->setGeometry(this->width()*70/192, this->height()*68/108, this->width()*51/192, this->height()*11/108);
    m_siege->setGeometry(this->width()*70/192, this->height()*80/108, this->width()*51/192, this->height()*11/108);
    o_card->setGeometry(this->width()*66/192, 0, this->width()*77/192, this->height()*11/108);
    o_melee->setGeometry(this->width()*70/192, this->height()*42/108, this->width()*51/192, this->height()*11/108);
    o_ranged->setGeometry(this->width()*70/192, this->height()*30/108, this->width()*51/192, this->height()*11/108);
    o_siege->setGeometry(this->width()*70/192, this->height()*18/108, this->width()*51/192, this->height()*11/108);
}

void BattleInterface::mouseMoveEvent(QMouseEvent *){

}
