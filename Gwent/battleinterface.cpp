#include "battleinterface.h"
#include "mainwindow.h"
#include <QDebug>

BattleInterface::BattleInterface(MainWindow *mw_, QWidget *parent) : QWidget(parent)
{
    mw = mw_;
    this->setMouseTracking(true);
    mw->get_player()->set_battle(this);
    turnlabel = new QLabel(this);
    turnlabel->setStyleSheet("background-color:transparent");

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
    edt->setVisible(false);
    edt->setTextColor(Qt::white);
    edt->setReadOnly(true);
    edt->setStyleSheet("background-color:transparent");

    m_meleescorelabel = new ScoreLabel(0, this);
    m_rangedscorelabel = new ScoreLabel(0, this);
    m_siegescorelabel = new ScoreLabel(0, this);
    m_totalscorelabel = new ScoreLabel(0, this);

    o_meleescorelabel = new ScoreLabel(0, this);
    o_rangedscorelabel = new ScoreLabel(0, this);
    o_siegescorelabel = new ScoreLabel(0, this);
    o_totalscorelabel = new ScoreLabel(0, this);

    m_deckshow = new ShowBattleCard(this);
    m_deckshow->setVisible(false);
    m_graveyardshow = new ShowBattleCard(this);
    m_graveyardshow->setVisible(false);
    m_cardshow = new ShowBattleCard(this);
    connect(m_cardshow, SIGNAL(send_hover_card(int)), this, SLOT(receive_hover_card_m_card(int)));
    connect(m_cardshow, SIGNAL(send_press_blank(int)), this, SLOT(receive_press_blank_m_card(int)));
    connect(m_cardshow, SIGNAL(send_press_card(int)), this, SLOT(receive_press_card_m_card(int)));
    m_meleeshow = new ShowBattleCard(this);
    connect(m_meleeshow, SIGNAL(send_hover_card(int)), this, SLOT(receive_hover_card_m_melee(int)));
    connect(m_meleeshow, SIGNAL(send_press_blank(int)), this, SLOT(receive_press_blank_m_melee(int)));
    connect(m_meleeshow, SIGNAL(send_press_card(int)), this, SLOT(receive_press_card_m_melee(int)));
    m_rangedshow = new ShowBattleCard(this);
    connect(m_rangedshow, SIGNAL(send_hover_card(int)), this, SLOT(receive_hover_card_m_ranged(int)));
    connect(m_rangedshow, SIGNAL(send_press_blank(int)), this, SLOT(receive_press_blank_m_ranged(int)));
    connect(m_rangedshow, SIGNAL(send_press_card(int)), this, SLOT(receive_press_card_m_ranged(int)));
    m_siegeshow = new ShowBattleCard(this);
    connect(m_siegeshow, SIGNAL(send_hover_card(int)), this, SLOT(receive_hover_card_m_siege(int)));
    connect(m_siegeshow, SIGNAL(send_press_blank(int)), this, SLOT(receive_press_blank_m_siege(int)));
    connect(m_siegeshow, SIGNAL(send_press_card(int)), this, SLOT(receive_press_card_m_siege(int)));

    o_deckshow = new ShowBattleCard(this);
    o_deckshow->setVisible(false);
    o_graveyardshow = new ShowBattleCard(this);
    o_graveyardshow->setVisible(false);
    o_cardshow = new ShowBattleCard(this);
    connect(o_cardshow, SIGNAL(send_hover_card(int)), this, SLOT(receive_hover_card_o_card(int)));
    connect(o_cardshow, SIGNAL(send_press_blank(int)), this, SLOT(receive_press_blank_o_card(int)));
    connect(o_cardshow, SIGNAL(send_press_card(int)), this, SLOT(receive_press_card_o_card(int)));
    o_meleeshow = new ShowBattleCard(this);
    connect(o_meleeshow, SIGNAL(send_hover_card(int)), this, SLOT(receive_hover_card_o_melee(int)));
    connect(o_meleeshow, SIGNAL(send_press_blank(int)), this, SLOT(receive_press_blank_o_melee(int)));
    connect(o_meleeshow, SIGNAL(send_press_card(int)), this, SLOT(receive_press_card_o_melee(int)));
    o_rangedshow = new ShowBattleCard(this);
    connect(o_rangedshow, SIGNAL(send_hover_card(int)), this, SLOT(receive_hover_card_o_ranged(int)));
    connect(o_rangedshow, SIGNAL(send_press_blank(int)), this, SLOT(receive_press_blank_o_ranged(int)));
    connect(o_rangedshow, SIGNAL(send_press_card(int)), this, SLOT(receive_press_card_o_ranged(int)));
    o_siegeshow = new ShowBattleCard(this);
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

    btnpass = new QPushButton(this);
    btnpass->setStyleSheet("border-image:url(:/images/pass)");
    connect(btnpass, SIGNAL(clicked(bool)), this, SLOT(send_pass()));

    btnsurrender = new QPushButton(this);
    btnsurrender->setStyleSheet("border-image:url(:/images/surrender)");
    connect(btnsurrender, SIGNAL(clicked(bool)), this, SLOT(send_surrender()));
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

    turnlabel->setGeometry(this->width()*10/192, this->height()*60/108, this->width()*20/192, this->height()*7/108);
    btnpass->setGeometry(this->width()*12/192, this->height()*43/108, this->width()*16/192, this->height()*6/108);
    btnsurrender->setGeometry(this->width()*12/192, this->height()*55/108, this->width()*16/192, this->height()*6/108);
}

void BattleInterface::mouseMoveEvent(QMouseEvent *){
    //qDebug() << event->pos();
    unshowcardinfo();
}

void BattleInterface::mousePressEvent(QMouseEvent *e){
    /*QPointer p = e->pos();
    QRect rect;
    rect = m_meleeshow->rect();
    if (rect.contains(p)){

    }*/
    mw->mGameClient->Send_Date("click: others");
}

void BattleInterface::loaddeck_m(QString msg){
    qDebug() << "loaddeck_m";
    //QStringList cardlist = msg.split(" ");
    m_deckshow->loadcards(msg);
    qDebug() << m_deckshow->get_cardlist()->size();
}

void BattleInterface::loaddeck_o(QString msg){
    qDebug() << "loaddeck_o";
    //QStringList cardlist = msg.split(" ");
    o_deckshow->loadcards(msg);
    qDebug() << o_deckshow->get_cardlist()->size();
}

void BattleInterface::pump_m(int num){
    qDebug() << "pump_m " << num;
    for (int i = 0; i < num; ++i){
        move(m_deckshow, 0, m_cardshow);
    }
}

void BattleInterface::pump_o(int num){
    for (int i = 0; i < num; ++i)
        move(o_deckshow, 0, o_cardshow);
}

void BattleInterface::Mulligantips(int num){
    QMessageBox tip(QMessageBox::NoIcon, "tips", "You can mulligan " + QString::number(num) + " cards!");
    QTimer *t = new QTimer(this);
    connect(t, SIGNAL(timeout()), &tip, SLOT(close()));
    t->setSingleShot(true);
    t->start(1000);
    tip.exec();
}

void BattleInterface::roundstarttips(int r){
    qDebug() << "roundstarttips";
    QMessageBox tip(QMessageBox::NoIcon, "tips", "Round "+QString::number(r)+"!");
    QTimer *t = new QTimer(this);
    connect(t, SIGNAL(timeout()), &tip, SLOT(close()));
    t->setSingleShot(true);
    t->start(1000);
    tip.exec();
}

void BattleInterface::roundendtips(int h){
    qDebug() << "roundendtips";
    QString msg;
    if (h == 0) msg = "You win this round!";
    else if (h == 1) msg = "You lose this round!";
    else msg = "Draw this round!";
    QMessageBox tip(QMessageBox::NoIcon, "tips", msg);
    QTimer *t = new QTimer(this);
    connect(t, SIGNAL(timeout()), &tip, SLOT(close()));
    t->setSingleShot(true);
    t->start(1000);
    tip.exec();
}

void BattleInterface::turntip(int h){
    if (h == 0) turnlabel->setStyleSheet("border-image:url(:/images/mturn)");
        else turnlabel->setStyleSheet("border-image:url(:/images/oturn)");
    updatescore();
}

ShowBattleCard * BattleInterface::convert(QString str, int type){
    ShowBattleCard *src;
    if (type == 0){
        if (str.compare("mdeck") == 0) src = m_deckshow;
        if (str.compare("mgraveyard") == 0) src = m_graveyardshow;
        if (str.compare("mcard") == 0) src = m_cardshow;
        if (str.compare("mmelee") == 0) src = m_meleeshow;
        if (str.compare("mranged") == 0) src = m_rangedshow;
        if (str.compare("msiege") == 0) src = m_siegeshow;
        if (str.compare("odeck") == 0) src = o_deckshow;
        if (str.compare("ograveyard") == 0) src = o_graveyardshow;
        if (str.compare("ocard") == 0) src = o_cardshow;
        if (str.compare("omelee") == 0) src = o_meleeshow;
        if (str.compare("oranged") == 0) src = o_rangedshow;
        if (str.compare("osiege") == 0) src = o_siegeshow;
    } else
    {
        if (str.compare("mdeck") == 0) src = o_deckshow;
        if (str.compare("mgraveyard") == 0) src = o_graveyardshow;
        if (str.compare("mcard") == 0) src = o_cardshow;
        if (str.compare("mmelee") == 0) src = o_meleeshow;
        if (str.compare("mranged") == 0) src = o_rangedshow;
        if (str.compare("msiege") == 0) src = o_siegeshow;
        if (str.compare("odeck") == 0) src = m_deckshow;
        if (str.compare("ograveyard") == 0) src = m_graveyardshow;
        if (str.compare("ocard") == 0) src = m_cardshow;
        if (str.compare("omelee") == 0) src = m_meleeshow;
        if (str.compare("oranged") == 0) src = m_rangedshow;
        if (str.compare("osiege") == 0) src = m_siegeshow;
    }
    return src;
}

void BattleInterface::move_m(QString info){
    qDebug() << "move_m";
    QStringList infolist = info.split(' ');
    ShowBattleCard *src, *tar;
    int srcid, tarid;
    QString str = infolist.at(0);
    src = convert(str);
    str = infolist.at(2);
    tar = convert(str);
    str = infolist.at(1);
    srcid = str.toInt();
    if (info.size() == 3){
        move(src, srcid, tar);
    } else
    {
        str = infolist.at(3);
        tarid = str.toInt();
        move(src, srcid, tar, tarid);
    }
}

void BattleInterface::move_o(QString info){
    qDebug() << "move_o";
    QStringList infolist = info.split(' ');
    ShowBattleCard *src, *tar;
    int srcid, tarid;
    QString str = infolist.at(0);
    src = convert(str, 1);
    str = infolist.at(2);
    tar = convert(str, 1);
    str = infolist.at(1);
    srcid = str.toInt();
    if (info.size() == 3){
        move(src, srcid, tar);
    } else
    {
        str = infolist.at(3);
        tarid = str.toInt();
        move(src, srcid, tar, tarid);
    }
}

void BattleInterface::replace_m(QString info){
    qDebug() << "replace_m";
    QStringList infolist = info.split(' ');
    ShowBattleCard *src, *tar;
    int srcid;
    src = m_deckshow;
    tar = m_cardshow;
    srcid = QString(infolist.at(1)).toInt();
    move(src, srcid, tar);

    src = m_cardshow;
    tar = m_deckshow;
    srcid = QString(infolist.at(0)).toInt();
    move(src, srcid, tar);
}

void BattleInterface::replace_o(QString info){
    qDebug() << "replace_o";
    QStringList infolist = info.split(' ');
    ShowBattleCard *src, *tar;
    int srcid;
    src = o_deckshow;
    tar = o_cardshow;
    srcid = QString(infolist.at(1)).toInt();
    move(src, srcid, tar);

    src = o_cardshow;
    tar = o_deckshow;
    srcid = QString(infolist.at(0)).toInt();
    move(src, srcid, tar);
}

void BattleInterface::move(ShowBattleCard *src, int srcid, ShowBattleCard *tar, int tarid){
    qDebug() << "move";
    QList<Card*> *srctmp = src->get_cardlist();
    qDebug() << srctmp->size();
    Card *srccard = srctmp->at(srcid);
    if (tarid == -1)
        tarid = tar->get_cardlist()->size();
    src->deleteonecard(srcid);
    tar->addonecard(srccard, tarid);

    src->Resize(src->width(), src->height());
    tar->Resize(tar->width(), tar->height());
}

void BattleInterface::gameover(int h){
    mw->get_player()->set_battle(nullptr);
    mw->setoverbackground(h);
    mw->switchstate(MainWindow::GameOver);
}

void BattleInterface::showcardinfo(Card* card_){
    edt->setVisible(true);
    QString str = card_->get_name() + "\n";
    if (card_->get_baseblood() > 0){
        str += "Blood: " + QString::number(card_->get_baseblood()) + "\n";
        str += "Boost: " + QString::number(card_->get_boostblood()) + "\n";
        str += "Armor: " + QString::number(card_->get_armor()) + "\n";
    }
    str += card_->get_rule() + "\n";
    str += card_->get_type() + "\n";
    edt->setText(str);
}

void BattleInterface::unshowcardinfo(){
    edt->setVisible(false);
}

void BattleInterface::updatescore(){
    m_meleescorelabel->set_score(m_meleeshow->get_score());
    m_rangedscorelabel->set_score(m_rangedshow->get_score());
    m_siegescorelabel->set_score(m_siegeshow->get_score());
    m_totalscorelabel->set_score(m_meleescorelabel->get_score() + m_rangedscorelabel->get_score() + m_siegescorelabel->get_score());

    o_meleescorelabel->set_score(o_meleeshow->get_score());
    o_rangedscorelabel->set_score(o_rangedshow->get_score());
    o_siegescorelabel->set_score(o_siegeshow->get_score());
    o_totalscorelabel->set_score(o_meleescorelabel->get_score() + o_rangedscorelabel->get_score() + o_siegescorelabel->get_score());
}

//前方高能
void BattleInterface::receive_press_card_m_card(int index){
    qDebug() << "receive_press_card_m_card " <<  index;
    mw->mGameClient->Send_Date("click: mcard " + QString::number(index));
}
void BattleInterface::receive_press_card_m_melee(int index){
    qDebug() << "receive_press_card_m_melee " <<  index;
    mw->mGameClient->Send_Date("click: mmelee " + QString::number(index));
}
void BattleInterface::receive_press_card_m_ranged(int index){
    qDebug() << "receive_press_card_m_ranged " << index;
    mw->mGameClient->Send_Date("click: mranged " + QString::number(index));
}
void BattleInterface::receive_press_card_m_siege(int index){
    qDebug() << "receive_press_card_m_siege " << index;
    mw->mGameClient->Send_Date("click: msiege " + QString::number(index));
}
void BattleInterface::receive_press_card_o_card(int index){
    qDebug() << "receive_press_card_o_card " << index;
    mw->mGameClient->Send_Date("click: ocard " + QString::number(index));
}
void BattleInterface::receive_press_card_o_melee(int index){
    qDebug() << "receive_press_card_o_melee " << index;
    mw->mGameClient->Send_Date("click: omelee " + QString::number(index));
}
void BattleInterface::receive_press_card_o_ranged(int index){
    qDebug() << "receive_press_card_o_ranged " << index;
    mw->mGameClient->Send_Date("click: oranged " + QString::number(index));
}
void BattleInterface::receive_press_card_o_siege(int index){
    qDebug() << "receive_press_card_o_siege " << index;
    mw->mGameClient->Send_Date("click: osiege " + QString::number(index));
}
void BattleInterface::receive_hover_card_m_card(int index){
    qDebug() << "receive_hover_card_m_card " << index;
    Card *tmp = m_cardshow->get_cardlist()->at(index);
    showcardinfo(tmp);
}
void BattleInterface::receive_hover_card_m_melee(int index){
    qDebug() << "receive_hover_card_m_melee " << index;
    Card *tmp = m_meleeshow->get_cardlist()->at(index);
    showcardinfo(tmp);
}
void BattleInterface::receive_hover_card_m_ranged(int index){
    qDebug() << "receive_hover_card_m_ranged " << index;
    Card *tmp = m_rangedshow->get_cardlist()->at(index);
    showcardinfo(tmp);
}
void BattleInterface::receive_hover_card_m_siege(int index){
    qDebug() << "receive_hover_card_m_siege " << index;
    Card *tmp = m_siegeshow->get_cardlist()->at(index);
    showcardinfo(tmp);
}
void BattleInterface::receive_hover_card_o_card(int index){
    qDebug() << "receive_hover_card_o_card " << index;
}
void BattleInterface::receive_hover_card_o_melee(int index){
    qDebug() << "receive_hover_card_o_melee " << index;
    Card *tmp = o_meleeshow->get_cardlist()->at(index);
    showcardinfo(tmp);
}
void BattleInterface::receive_hover_card_o_ranged(int index){
    qDebug() << "receive_hover_card_o_ranged " << index;
    Card *tmp = o_rangedshow->get_cardlist()->at(index);
    showcardinfo(tmp);
}
void BattleInterface::receive_hover_card_o_siege(int index){
    qDebug() << "receive_hover_card_o_siege " << index;
    Card *tmp = m_siegeshow->get_cardlist()->at(index);
    showcardinfo(tmp);
}
void BattleInterface::receive_press_blank_m_card(int index){
    qDebug() << "receive_press_blank_m_card " << index;
    mw->mGameClient->Send_Date("click: blank mcard " + QString::number(index));
}
void BattleInterface::receive_press_blank_m_melee(int index){
    qDebug() << "receive_press_blank_m_melee " << index;
    mw->mGameClient->Send_Date("click: blank mmelee " + QString::number(index));
}
void BattleInterface::receive_press_blank_m_ranged(int index){
    qDebug() << "receive_press_blank_m_ranged " << index;
    mw->mGameClient->Send_Date("click: blank mranged " + QString::number(index));
}
void BattleInterface::receive_press_blank_m_siege(int index){
    qDebug() << "receive_press_blank_m_siege " << index;
    mw->mGameClient->Send_Date("click: blank msiege " + QString::number(index));
}
void BattleInterface::receive_press_blank_o_card(int index){
    qDebug() << "receive_press_blank_o_card " << index;
    mw->mGameClient->Send_Date("click: blank ocard " + QString::number(index));
}
void BattleInterface::receive_press_blank_o_melee(int index){
    qDebug() << "receive_press_blank_o_melee " << index;
    mw->mGameClient->Send_Date("click: blank omelee " + QString::number(index));
}
void BattleInterface::receive_press_blank_o_ranged(int index){
    qDebug() << "receive_press_blank_o_ranged " << index;
    mw->mGameClient->Send_Date("click: blank oranged " + QString::number(index));
}
void BattleInterface::receive_press_blank_o_siege(int index){
    qDebug() << "receive_press_blank_o_siege " << index;
    mw->mGameClient->Send_Date("click: blank osiege " + QString::number(index));
}

void BattleInterface::send_surrender(){
    mw->mGameClient->Send_Date("surrender");
}

void BattleInterface::send_pass(){
    mw->mGameClient->Send_Date("pass");
}
