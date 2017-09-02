#include "welcomeinterface.h"

WelcomeInterface::WelcomeInterface(QWidget *parent) : QWidget(parent)
{
    /*QPalette palette;
    QPixmap pixmap(":/images/welcome_background");
    //palette.setBrush(QPalette::Window, QBrush(pixmap));
    palette.setBrush(this->backgroundRole(), QBrush(pixmap));
    this->setPalette(palette);
    this->setAutoFillBackground(true);

    this->setWindowFlags(Qt::WindowMinMaxButtonsHint);*/
    //this->setObjectName("Welcome");
    //this->setStyleSheet("WelcomeInterface#Welcome{border-image:url(qrc:/images/welcome_background)}");
    //this->show();
}


WelcomeInterface::~WelcomeInterface(){

}

void WelcomeInterface::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/welcome_background"));
}
