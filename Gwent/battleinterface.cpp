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

    for (int i = 0; i < 12; ++i){
        qsa[i] = new QScrollArea(this);
        qsa[i]->setStyleSheet("background-color:transparent");
        if (i >= 8) qsa[i]->setVisible(false);
        sky[i] = clean;
    }

    edt = new QTextEdit(this);
    edt->setVisible(false);
    edt->setTextColor(Qt::white);
    edt->setReadOnly(true);
    edt->setStyleSheet("background-color:transparent");

    for (int i = 0; i < 8; ++i){
        scoreLabel[i] = new ScoreLabel(0, this);
    }

    for (int i = 0; i < 12; ++i){
        shows[i] = new ShowBattleCard(this);
        shows[i]->setid(i);
        if (i < 8){
            connect(shows[i], SIGNAL(send_hover_card(int, int)), this, SLOT(receive_hover_card(int, int)));
            connect(shows[i], SIGNAL(send_press_blank(int, int)), this, SLOT(receive_press_blank(int, int)));
            connect(shows[i], SIGNAL(send_press_card(int, int)), this, SLOT(receive_press_card(int, int)));
            qsa[i]->setWidget(shows[i]);
        } else
        {
            shows[i]->setVisible(false);
        }
    }
    btnpass = new QPushButton(this);
    btnpass->setStyleSheet("border-image:url(:/images/pass)");
    connect(btnpass, SIGNAL(clicked(bool)), this, SLOT(send_pass()));

    btnsurrender = new QPushButton(this);
    btnsurrender->setStyleSheet("border-image:url(:/images/surrender)");
    connect(btnsurrender, SIGNAL(clicked(bool)), this, SLOT(send_surrender()));

    btnendmulligan = new QPushButton(this);
    btnendmulligan->setStyleSheet("border-image:url(:/images/endmulligan)");
    btnendmulligan->setVisible(false);
    connect(btnendmulligan, SIGNAL(clicked(bool)), this, SLOT(send_endmulligan()));

    score[0] = score[1] = 0;
}

void BattleInterface::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/battleboard"));

    painter.setPen(Qt::white);
    painter.drawText(this->width()*45/192, this->height()*6/108, QString::number(shows[1]->get_cardlist()->size()));
    painter.drawText(this->width()*45/192, this->height()*102/108, QString::number(shows[0]->get_cardlist()->size()));
    painter.drawText(this->width()*152/192, this->height()*6/108, QString::number(shows[9]->get_cardlist()->size()));
    painter.drawText(this->width()*152/192, this->height()*102/108, QString::number(shows[8]->get_cardlist()->size()));
    painter.drawText(this->width()*186/192, this->height()*6/108, QString::number(shows[11]->get_cardlist()->size()));
    painter.drawText(this->width()*186/192, this->height()*102/108, QString::number(shows[10]->get_cardlist()->size()));

    painter.drawPixmap(this->width()*13/192, this->height()*31/108, this->width()*95/1920, this->height()*8/108, QPixmap(":/images/score"+QString::number(score[1])));
    painter.drawPixmap(this->width()*13/192, this->height()*69/108, this->width()*95/1920, this->height()*8/108, QPixmap(":/images/score"+QString::number(score[0])));

    QString pic[12];
    for (int i = 2; i < 8; ++i){
        if (sky[i] == clean) continue;
        switch (sky[i]) {
        case fog:
            pic[i] = ":/images/fog";
            break;
        case frost:
            pic[i] = ":/images/frost";
            break;
        case rain:
            pic[i] = ":/images/rain";
            break;
        default:
            pic[i] = "";
            break;
        }
    }
    if (pic[2].compare("")!=0)
    painter.drawPixmap(this->width()*55/192, this->height()*80/108, this->width()*81/192, this->height()*10/108, QPixmap(pic[2]));
    if (pic[4].compare("")!=0)
    painter.drawPixmap(this->width()*55/192, this->height()*68/108, this->width()*81/192, this->height()*10/108, QPixmap(pic[4]));
    if (pic[6].compare("")!=0)
    painter.drawPixmap(this->width()*55/192, this->height()*56/108, this->width()*81/192, this->height()*10/108, QPixmap(pic[6]));
    if (pic[7].compare("")!=0)
    painter.drawPixmap(this->width()*55/192, this->height()*42/108, this->width()*81/192, this->height()*10/108, QPixmap(pic[7]));
    if (pic[5].compare("")!=0)
    painter.drawPixmap(this->width()*55/192, this->height()*30/108, this->width()*81/192, this->height()*10/108, QPixmap(pic[5]));
    if (pic[3].compare("")!=0)
    painter.drawPixmap(this->width()*55/192, this->height()*18/108, this->width()*81/192, this->height()*10/108, QPixmap(pic[3]));
}

void BattleInterface::resizeEvent(QResizeEvent *){
    qsa[0]->setGeometry(this->width()*66/192, this->height()*97/108, this->width()*77/192, this->height()*11/108);
    qsa[6]->setGeometry(this->width()*70/192, this->height()*56/108, this->width()*51/192, this->height()*11/108);
    qsa[4]->setGeometry(this->width()*70/192, this->height()*68/108, this->width()*51/192, this->height()*11/108);
    qsa[2]->setGeometry(this->width()*70/192, this->height()*80/108, this->width()*51/192, this->height()*11/108);
    qsa[1]->setGeometry(this->width()*66/192, 0, this->width()*77/192, this->height()*11/108);
    qsa[7]->setGeometry(this->width()*70/192, this->height()*42/108, this->width()*51/192, this->height()*11/108);
    qsa[5]->setGeometry(this->width()*70/192, this->height()*30/108, this->width()*51/192, this->height()*11/108);
    qsa[3]->setGeometry(this->width()*70/192, this->height()*18/108, this->width()*51/192, this->height()*11/108);

    edt->setGeometry(this->width()*159/192, this->height()*22/108, this->width()*21/192, this->height()*32/108);

    for (int i = 0; i < 8; ++i)
        shows[i]->Resize(qsa[i]->width(), qsa[i]->height());

    turnlabel->setGeometry(this->width()*10/192, this->height()*60/108, this->width()*20/192, this->height()*7/108);
    btnpass->setGeometry(this->width()*12/192, this->height()*43/108, this->width()*16/192, this->height()*6/108);
    btnsurrender->setGeometry(this->width()*12/192, this->height()*53/108, this->width()*16/192, this->height()*6/108);
    btnendmulligan->setGeometry(this->width()*12/192, this->height()*83/108, this->width()*16/192, this->height()*6/108);

    layout_score();
}

void BattleInterface::layout_score(){
    scoreLabel[6]->setGeometry(this->width()*415/1920, this->height()*570/1080, this->width()*8/192, this->height()*8/108);
    scoreLabel[4]->setGeometry(this->width()*415/1920, this->height()*690/1080, this->width()*8/192, this->height()*8/108);
    scoreLabel[2]->setGeometry(this->width()*415/1920, this->height()*805/1080, this->width()*8/192, this->height()*8/108);
    scoreLabel[0]->setGeometry(this->width()*270/1920, this->height()*700/1080, this->width()*8/192, this->height()*8/108);

    scoreLabel[7]->setGeometry(this->width()*415/1920, this->height()*430/1080, this->width()*8/192, this->height()*8/108);
    scoreLabel[5]->setGeometry(this->width()*415/1920, this->height()*310/1080, this->width()*8/192, this->height()*8/108);
    scoreLabel[3]->setGeometry(this->width()*415/1920, this->height()*195/1080, this->width()*8/192, this->height()*8/108);
    scoreLabel[1]->setGeometry(this->width()*270/1920, this->height()*315/1080, this->width()*8/192, this->height()*8/108);
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

void BattleInterface::loaddeck(int x, QString msg){
    qDebug() << "loaddeck" << x << msg;
    //QStringList cardlist = msg.split(" ");
    shows[10^x]->loadcards(msg);
    qDebug() << shows[10^x]->get_cardlist()->size();
}

void BattleInterface::pump(int x, int num){
    qDebug() << "pump " << x << num;
    for (int i = 0; i < num; ++i){
        move(10^x, 0, x);
    }
}

void BattleInterface::Mulligantips(int num){
    btnendmulligan->setVisible(true);
    QMessageBox tip(QMessageBox::NoIcon, "tips", "You can mulligan " + QString::number(num) + " cards!");
    QTimer *t = new QTimer(this);
    connect(t, SIGNAL(timeout()), &tip, SLOT(close()));
    t->setSingleShot(true);
    t->start(1000);
    tip.exec();
}

void BattleInterface::roundstarttips(int r){
    btnendmulligan->setVisible(false);
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
    if (h == 0) msg = "You win this round!", score[0]++;
    else if (h == 1) msg = "You lose this round!", score[1]++;
    else msg = "Draw this round!", score[0]++, score[1]++;

    if (score[0] == 2 && score[1] == 2){
        gameover(2);
        return;
    } else
    if (score[0] == 2){
        gameover(0);
        return;
    } else
    if (score[1] == 2){
        gameover(1);
        return;
    }

    QMessageBox tip(QMessageBox::NoIcon, "Tips", msg);
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

void BattleInterface::move(QString info){
    qDebug() << "move" << info;
    QStringList infolist = info.split(' ');
    int i1 = infolist.at(0).toInt();
    int j1 = infolist.at(1).toInt();
    int i2 = infolist.at(2).toInt();
    if (infolist.size() == 3){
        move(i1, j1, i2);
    } else
    {
        int j2 = infolist.at(3).toInt();
        move(i1, j1, i2, j2);
    }
}

void BattleInterface::move(int i1, int j1, int i2, int j2){
    qDebug() << "move";
    QList<Card*> *srctmp = shows[i1]->get_cardlist();
    qDebug() << srctmp->size();
    Card *srccard = srctmp->at(j1);
    if (j2 == -1) j2 = shows[i2]->get_cardlist()->size();
    shows[i1]->deleteonecard(j1);
    shows[i2]->addonecard(srccard, j2);

    shows[i1]->Resize(shows[i1]->width(), shows[i1]->height());
    shows[i2]->Resize(shows[i2]->width(), shows[i2]->height());
    updatescore();
    this->update();
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
        if (card_->get_ARMOR())
            str += "Shield\n";
    }
    str += card_->get_rule() + "\n";
    str += card_->get_type() + "\n";
    edt->setText(str);
}

void BattleInterface::unshowcardinfo(){
    edt->setVisible(false);
}

void BattleInterface::updatescore(){
    int t[2];
    t[0] = t[1] = 0;
    for (int i = 2; i < 8; ++i){
        int tmp = shows[i]->get_score();
        t[i&1] += tmp;
        scoreLabel[i]->set_score(tmp);
    }
    scoreLabel[0]->set_score(t[0]);
    scoreLabel[1]->set_score(t[1]);

    layout_score();
}

void BattleInterface::receive_hover_card(int index1, int index2){
    qDebug() << "receive_hover_card" << index1 << index2;
    Card *tmp = shows[index1]->get_cardlist()->at(index2);
    showcardinfo(tmp);
}

void BattleInterface::receive_press_card(int index1, int index2){
    qDebug() << "receive_press_card" << index1 << index2;
    mw->mGameClient->Send_Date("click: " + QString::number(index1) + " " + QString::number(index2));
}

void BattleInterface::receive_press_blank(int index1, int index2){
    qDebug() << "receive_press_blank" << index1 << index2;
    mw->mGameClient->Send_Date("click: b " + QString::number(index1) + " " + QString::number(index2));
}

void BattleInterface::send_surrender(){
    mw->mGameClient->Send_Date("surrender");
}

void BattleInterface::send_pass(){
    mw->mGameClient->Send_Date("pass");
}

void BattleInterface::bloodchange(QString info){
    QStringList lt = info.split(' ');
    int x = lt.at(0).toInt();
    int y = lt.at(1).toInt();
    int dlt1 = lt.at(2).toInt();
    int dlt2 = lt.at(3).toInt();
    int dlt3 = lt.at(4).toInt();
    //qDebug() << "bloodchange" << dlt1 << dlt2 << dlt3;
    shows[x]->get_cardlist()->at(y)->add_armor(dlt3);
    //qDebug() << shows[x]->get_cardlist()->at(y)->get_baseblood();
    shows[x]->get_cardlist()->at(y)->add_boost(dlt2);
    //qDebug() << shows[x]->get_cardlist()->at(y)->get_baseblood();
    shows[x]->get_cardlist()->at(y)->add_base(dlt1);
    //qDebug() << shows[x]->get_cardlist()->at(y)->get_baseblood();
    this->update();
}

void BattleInterface::set_sky(QString info){
    QStringList lt = info.split(' ');
    int x = lt.at(0).toInt();
    int y = lt.at(1).toInt();
    if (y == 0) sky[x] = clean;
    if (y == 1) sky[x] = fog;
    if (y == 2) sky[x] = frost;
    if (y == 3) sky[x] = rain;
    this->update();
}

void BattleInterface::addnewcard(QString info){
    QStringList infolist = info.split(' ');
    Card *card = new Card(infolist.at(0).toInt());
    int x = infolist.at(1).toInt();
    int y;
    if (infolist.size() == 3)
        y = infolist.at(2).toInt();
    else y = shows[x]->get_cardlist()->size();

    shows[x]->addonecard(card, y);
    shows[x]->Resize(qsa[x]->width(), qsa[x]->height());

}

void BattleInterface::get_ARMOR(QString info){
    QStringList infolist = info.split(' ');
    int index1 = infolist.at(0).toInt();
    int index2 = infolist.at(1).toInt();
    shows[index1]->get_cardlist()->at(index2)->set_ARMOR(true);
}

void BattleInterface::send_endmulligan(){
    mw->mGameClient->Send_Date("endmulligan");
}
