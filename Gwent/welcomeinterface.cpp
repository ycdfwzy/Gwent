#include "welcomeinterface.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>

WelcomeInterface::WelcomeInterface(MainWindow *mw_, QWidget *parent) : QWidget(parent)
{
    mw = mw_;
    this->setFocusPolicy(Qt::StrongFocus);
}

WelcomeInterface::~WelcomeInterface(){}

void WelcomeInterface::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/welcome_background"));
}

void WelcomeInterface::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        QMessageBox::about(this, tr("mousepress"), tr("Press!"));
        mw->mGameClient = new gameClient(mw);
    }
}

void WelcomeInterface::keyPressEvent(QKeyEvent *event){
    //qDebug() << event->key();
    if (event->key() == Qt::Key_Return){
        QMessageBox::about(this, tr("keypress"), tr("Press!"));
        mw->mGameClient = new gameClient(mw);
    }
}
