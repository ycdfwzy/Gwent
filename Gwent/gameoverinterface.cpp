#include "gameoverinterface.h"
#include "mainwindow.h"
#include <QDebug>

GameoverInterface::GameoverInterface(MainWindow *mw_, QWidget *parent) : QWidget(parent)
{
    mw = mw_;
    btnexit = new QPushButton(this);
    btnexit->setStyleSheet("border-image:url(:/images/btnexit)");
    connect(btnexit, SIGNAL(clicked(bool)), this, SLOT(back_home()));
}

void GameoverInterface::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(mw->get_overbackground()));
}

void GameoverInterface::resizeEvent(QResizeEvent *){
    btnexit->setGeometry(this->width()*911/1920, this->height()*1003/1080, this->width()*95/1920, this->height()*4/108);
}

void GameoverInterface::back_home(){
    mw->switchstate(MainWindow::Home);
}
