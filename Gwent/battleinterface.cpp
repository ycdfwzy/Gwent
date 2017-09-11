#include "battleinterface.h"
#include "mainwindow.h"
#include <QDebug>

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

    edt = new QTextEdit(this);
    //edt->setVisible(false);
    edt->setReadOnly(true);
    edt->setStyleSheet("background-color:transparent");

    m_meleescorelabel = new ScoreLabel(0, this);
    m_rangedscorelabel = new ScoreLabel(10, this);
    m_siegescorelabel = new ScoreLabel(80, this);
    m_totalscorelabel = new ScoreLabel(0, this);

    o_meleescorelabel = new ScoreLabel(99, this);
    o_rangedscorelabel = new ScoreLabel(100, this);
    o_siegescorelabel = new ScoreLabel(0, this);
    o_totalscorelabel = new ScoreLabel(888, this);

    m_graveyardshow = new ShowBattleCard("10 101", this);
    m_cardshow = new ShowBattleCard("16 166", this);
    connect(m_cardshow, SIGNAL(send_hover_card(int)), this, SLOT(receive_hover_card_m_card(int)));
    connect(m_cardshow, SIGNAL(send_press_blank(int)), this, SLOT(receive_press_blank_m_card(int)));
    connect(m_cardshow, SIGNAL(send_press_card(int)), this, SLOT(receive_press_card_m_card(int)));
    m_meleeshow = new ShowBattleCard("167 169", this);
    connect(m_meleeshow, SIGNAL(send_hover_card(int)), this, SLOT(receive_hover_card_m_melee(int)));
    connect(m_meleeshow, SIGNAL(send_press_blank(int)), this, SLOT(receive_press_blank_m_melee(int)));
    connect(m_meleeshow, SIGNAL(send_press_card(int)), this, SLOT(receive_press_card_m_melee(int)));
    m_rangedshow = new ShowBattleCard("17 171", this);
    connect(m_rangedshow, SIGNAL(send_hover_card(int)), this, SLOT(receive_hover_card_m_ranged(int)));
    connect(m_rangedshow, SIGNAL(send_press_blank(int)), this, SLOT(receive_press_blank_m_ranged(int)));
    connect(m_rangedshow, SIGNAL(send_press_card(int)), this, SLOT(receive_press_card_m_ranged(int)));
    m_siegeshow = new ShowBattleCard("18 181", this);
    connect(m_siegeshow, SIGNAL(send_hover_card(int)), this, SLOT(receive_hover_card_m_siege(int)));
    connect(m_siegeshow, SIGNAL(send_press_blank(int)), this, SLOT(receive_press_blank_m_siege(int)));
    connect(m_siegeshow, SIGNAL(send_press_card(int)), this, SLOT(receive_press_card_m_siege(int)));

    o_graveyardshow = new ShowBattleCard("182 183", this);
    o_cardshow = new ShowBattleCard("188 19", this);
    connect(o_cardshow, SIGNAL(send_hover_card(int)), this, SLOT(receive_hover_card_o_card(int)));
    connect(o_cardshow, SIGNAL(send_press_blank(int)), this, SLOT(receive_press_blank_o_card(int)));
    connect(o_cardshow, SIGNAL(send_press_card(int)), this, SLOT(receive_press_card_o_card(int)));
    o_meleeshow = new ShowBattleCard("225 236", this);
    connect(o_meleeshow, SIGNAL(send_hover_card(int)), this, SLOT(receive_hover_card_o_melee(int)));
    connect(o_meleeshow, SIGNAL(send_press_blank(int)), this, SLOT(receive_press_blank_o_melee(int)));
    connect(o_meleeshow, SIGNAL(send_press_card(int)), this, SLOT(receive_press_card_o_melee(int)));
    o_rangedshow = new ShowBattleCard("256 281", this);
    connect(o_rangedshow, SIGNAL(send_hover_card(int)), this, SLOT(receive_hover_card_o_ranged(int)));
    connect(o_rangedshow, SIGNAL(send_press_blank(int)), this, SLOT(receive_press_blank_o_ranged(int)));
    connect(o_rangedshow, SIGNAL(send_press_card(int)), this, SLOT(receive_press_card_o_ranged(int)));
    o_siegeshow = new ShowBattleCard("294", this);
    connect(o_siegeshow, SIGNAL(send_hover_card(int)), this, SLOT(receive_hover_card_o_siege(int)));
    connect(o_siegeshow, SIGNAL(send_press_blank(int)), this, SLOT(receive_press_blank_o_siege(int)));
    connect(o_siegeshow, SIGNAL(send_press_card(int)), this, SLOT(receive_press_card_o_siege(int)));

    m_card->setWidget(m_cardshow);
    m_melee->setWidget(m_meleeshow);
    m_ranged->setWidget(m_rangedshow);
    m_siege->setWidget(m_siegeshow);

    o_card->setWidget(o_cardshow);
    o_melee->setWidget(o_meleeshow);
    o_ranged->setWidget(o_rangedshow);
    o_siege->setWidget(o_siegeshow);
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
    edt->setGeometry(this->width()*159/192, this->height()*22/108, this->width()*21/192, this->height()*32/108);

    m_meleescorelabel->setGeometry(this->width()*415/1920, this->height()*570/1080, this->width()*8/192, this->height()*8/108);
    m_rangedscorelabel->setGeometry(this->width()*415/1920, this->height()*690/1080, this->width()*8/192, this->height()*8/108);
    m_siegescorelabel->setGeometry(this->width()*415/1920, this->height()*805/1080, this->width()*8/192, this->height()*8/108);
    m_totalscorelabel->setGeometry(this->width()*270/1920, this->height()*700/1080, this->width()*8/192, this->height()*8/108);

    o_meleescorelabel->setGeometry(this->width()*415/1920, this->height()*430/1080, this->width()*8/192, this->height()*8/108);
    o_rangedscorelabel->setGeometry(this->width()*415/1920, this->height()*310/1080, this->width()*8/192, this->height()*8/108);
    o_siegescorelabel->setGeometry(this->width()*415/1920, this->height()*195/1080, this->width()*8/192, this->height()*8/108);
    o_totalscorelabel->setGeometry(this->width()*270/1920, this->height()*315/1080, this->width()*8/192, this->height()*8/108);

    m_cardshow->Resize(m_card->width(), m_card->height());
    m_meleeshow->Resize(m_melee->width(), m_melee->height());
    m_rangedshow->Resize(m_ranged->width(), m_ranged->height());
    m_siegeshow->Resize(m_siege->width(), m_siege->height());

    o_cardshow->Resize(o_card->width(), o_card->height());
    o_meleeshow->Resize(o_melee->width(), o_melee->height());
    o_rangedshow->Resize(o_ranged->width(), o_ranged->height());
    o_siegeshow->Resize(o_siege->width(), o_siege->height());
}

void BattleInterface::mouseMoveEvent(QMouseEvent *event){
    //qDebug() << event->pos();
}

//前方高能

void BattleInterface::receive_press_card_m_card(int index){
    qDebug() << "receive_press_card_m_card " <<  index;
}
void BattleInterface::receive_press_card_m_melee(int index){
    qDebug() << "receive_press_card_m_melee " <<  index;
}
void BattleInterface::receive_press_card_m_ranged(int index){
    qDebug() << "receive_press_card_m_ranged " << index;
}
void BattleInterface::receive_press_card_m_siege(int index){
    qDebug() << "receive_press_card_m_siege " << index;
}
void BattleInterface::receive_press_card_o_card(int index){
    qDebug() << "receive_press_card_o_card " << index;
}
void BattleInterface::receive_press_card_o_melee(int index){
    qDebug() << "receive_press_card_o_melee " << index;
}
void BattleInterface::receive_press_card_o_ranged(int index){
    qDebug() << "receive_press_card_o_ranged " << index;
}
void BattleInterface::receive_press_card_o_siege(int index){
    qDebug() << "receive_press_card_o_siege " << index;
}
void BattleInterface::receive_hover_card_m_card(int index){
    qDebug() << "receive_hover_card_m_card " << index;
}
void BattleInterface::receive_hover_card_m_melee(int index){
    qDebug() << "receive_hover_card_m_melee " << index;
}
void BattleInterface::receive_hover_card_m_ranged(int index){
    qDebug() << "receive_hover_card_m_ranged " << index;
}
void BattleInterface::receive_hover_card_m_siege(int index){
    qDebug() << "receive_hover_card_m_siege " << index;
}
void BattleInterface::receive_hover_card_o_card(int index){
    qDebug() << "receive_hover_card_o_card " << index;
}
void BattleInterface::receive_hover_card_o_melee(int index){
    qDebug() << "receive_hover_card_o_melee " << index;
}
void BattleInterface::receive_hover_card_o_ranged(int index){
    qDebug() << "receive_hover_card_o_ranged " << index;
}
void BattleInterface::receive_hover_card_o_siege(int index){
    qDebug() << "receive_hover_card_o_siege " << index;
}
void BattleInterface::receive_press_blank_m_card(int index){
    qDebug() << "receive_press_blank_m_card " << index;
}
void BattleInterface::receive_press_blank_m_melee(int index){
    qDebug() << "receive_press_blank_m_melee " << index;
}
void BattleInterface::receive_press_blank_m_ranged(int index){
    qDebug() << "receive_press_blank_m_ranged " << index;
}
void BattleInterface::receive_press_blank_m_siege(int index){
    qDebug() << "receive_press_blank_m_siege " << index;
}
void BattleInterface::receive_press_blank_o_card(int index){
    qDebug() << "receive_press_blank_o_card " << index;
}
void BattleInterface::receive_press_blank_o_melee(int index){
    qDebug() << "receive_press_blank_o_melee " << index;
}
void BattleInterface::receive_press_blank_o_ranged(int index){
    qDebug() << "receive_press_blank_o_ranged " << index;
}
void BattleInterface::receive_press_blank_o_siege(int index){
    qDebug() << "receive_press_blank_o_siege " << index;
}
