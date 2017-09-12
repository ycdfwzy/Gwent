#include "waitbattleinterface.h"
#include "mainwindow.h"

WaitBattleInterface::WaitBattleInterface(MainWindow *mw_, QWidget *parent) : QWidget(parent)
{
    mw = mw_;

    stopbtn = new QPushButton(this);
    stopbtn->setStyleSheet("border-image: url(:/images/btnstop)");
    connect(stopbtn, &QPushButton::clicked, this, &WaitBattleInterface::stopbtnClicked);

    tips = new QLabel(this);
    //tips->setPixmap(QPixmap(":/images/wait"));
    tips->setStyleSheet("border-image: url(:/images/wait)");

    Slide = nullptr;
    animation = nullptr;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(restartanimation()));
    timer->start(1000);

    //connect(mw->mGameClient, SIGNAL(foundsignal()), this, SLOT(hasfound()));
    mw->mGameClient->set_wbi(this);
    /*QTimer *t =  new QTimer(this);
    connect(t, SIGNAL(timeout()), this, SLOT(hasfound()));
    t->start(10000);*/
}

WaitBattleInterface::~WaitBattleInterface(){}

void WaitBattleInterface::restartanimation(){
    //qDebug() << "restartanimation";
    if (Slide == nullptr){
        Slide = new QPushButton(this);
        Slide->setVisible(true);
        Slide->setStyleSheet("border-image: url(:/images/slide)");
    }

    if (animation == nullptr){
        animation = new QPropertyAnimation(Slide, "geometry");
        animation->setDuration(1000);
    }

    animation->setStartValue(QRect(0, this->height()*86/108, this->width()*24/192, this->height()*6/108));
    animation->setEndValue(QRect(this->width(), this->height()*86/108, this->width()*24/192, this->height()*6/108));

    animation->start();
}

void WaitBattleInterface::hasfound(){
    //qDebug() << "hasfound";
    tips->setStyleSheet("border-image: url(:/images/found)");

    disconnect(timer, SIGNAL(timeout()), this, SLOT(restartanimation()));

    startbattle();
    //connect(timer, SIGNAL(timeout()), this, SLOT(startbattle()));
    //timer->setSingleShot(true);
    //timer->start(1000);
}

void WaitBattleInterface::startbattle(){
    //qDebug() << "startbattle";
    mw->switchstate(MainWindow::Playing);
}

void WaitBattleInterface::stopbtnClicked(){
    //send msg to server
    QString msg = "STOPMATCH!";
    mw->mGameClient->Send_Date(msg);
    mw->switchstate(MainWindow::Home);
}

void WaitBattleInterface::paintEvent(QPaintEvent*){
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/waiting"));
}

void WaitBattleInterface::resizeEvent(QResizeEvent*){
    stopbtn->setGeometry(this->width()*84/192, this->height()*95/108, this->width()*24/192, this->height()*6/108);
    tips->setGeometry(this->width()*84/192, this->height()*80/108, this->width()*24/192, this->height()*6/108);
}
