#include "waitinterface.h"
#include "mainwindow.h"

WaitInterface::WaitInterface(MainWindow *mw_, QWidget *parent) : QWidget(parent)
{
    mw = mw_;
    //this->setStyleSheet("border-image: url(:/images/waiting);");

    stopbtn = new QPushButton(tr("停止匹配"));
    connect(stopbtn, &QPushButton::clicked, this, &WaitInterface::stopbtnClicked);

    QGridLayout *gl = new QGridLayout;
    gl->setRowStretch(0, 100);
    gl->setRowStretch(1, 100);
    gl->setRowStretch(2, 100);
    gl->setColumnStretch(0, 100);
    gl->setColumnStretch(1, 100);
    gl->setColumnStretch(2, 100);
    gl->addWidget(stopbtn, 2, 1, 1, 1);

    this->setLayout(gl);

    //send msg to msg
}

WaitInterface::~WaitInterface(){}

void WaitInterface::stopbtnClicked(){
    //send msg to server
    mw->switchstate(MainWindow::Home);
}

void WaitInterface::paintEvent(QPaintEvent*){
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/waiting"));
}
