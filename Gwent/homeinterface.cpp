#include "homeinterface.h"
#include "mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QPixmap>
#include <QPalette>
#include <QBrush>
#include <QStyleOption>
/*
MyPushButton::MyPushButton(){}

MyPushButton::~MyPushButton(){}

void MyPushButton::paintEvent(QPaintEvent *){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
*/
HomeInterface::HomeInterface(MainWindow *mw_, QWidget *parent) : QWidget(parent)
{
    mw = mw_;
    btnplay = new QPushButton();
    QFile qssplay(":/style/playstyle");
    qssplay.open(QFile::ReadOnly);
    btnplay->setStyleSheet(qssplay.readAll());
    qssplay.close();
    btnplay->setFixedSize(330, 220);
    connect(btnplay, &QPushButton::clicked, this, &HomeInterface::btnplayClicked);

    btnedit = new QPushButton();
    QFile qssedit(":/style/editstyle");
    qssedit.open(QFile::ReadOnly);
    btnedit->setStyleSheet(qssedit.readAll());
    qssedit.close();
    btnedit->setFixedSize(330, 220);
    connect(btnedit, &QPushButton::clicked, this, &HomeInterface::btneditClicked);

    QGridLayout *gl = new QGridLayout;
    gl->setColumnStretch(0, 100);
    gl->setColumnStretch(1, 100);
    gl->setColumnStretch(2, 100);
    gl->setRowStretch(0, 100);
    gl->setRowStretch(1, 100);
    gl->setRowStretch(2, 100);
    gl->addWidget(btnplay, 2, 0, 1, 1);
    gl->addWidget(btnedit, 2, 2, 1, 1);
    this->setLayout(gl);
}

HomeInterface::~HomeInterface(){}

void HomeInterface::paintEvent(QPaintEvent*){
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/home_background"));
}

void HomeInterface::btnplayClicked(){
    mw->switchstate(MainWindow::Waiting);
}

void HomeInterface::btneditClicked(){
    mw->switchstate(MainWindow::EditDeck);
}
