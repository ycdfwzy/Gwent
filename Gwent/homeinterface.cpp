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
    btnplay = new QPushButton(this);
    QFile qssplay(":/style/playstyle");
    qssplay.open(QFile::ReadOnly);
    btnplay->setStyleSheet(qssplay.readAll());
    qssplay.close();
    btnplay->setGeometry(this->width()*64/1920, this->height()*312/1080, this->width()*617/1920, this->height()*435/1080);
    connect(btnplay, &QPushButton::clicked, this, &HomeInterface::btnplayClicked);

    btnmatch = new QPushButton(this);
    QFile qssmatch(":/style/matchstyle");
    qssmatch.open(QFile::ReadOnly);
    btnmatch->setStyleSheet(qssmatch.readAll());
    qssmatch.close();
    btnmatch->setGeometry(this->width()*716/1920, this->height()*312/1080, this->width()*306/1920, this->height()*435/1080);
    connect(btnmatch, &QPushButton::clicked, this, &HomeInterface::btnmatchClicked);

    btnedit = new QPushButton(this);
    QFile qssedit(":/style/editstyle");
    qssedit.open(QFile::ReadOnly);
    btnedit->setStyleSheet(qssedit.readAll());
    qssedit.close();
    btnedit->setGeometry(this->width()*1060/1920, this->height()*312/1080, this->width()*617/1920, this->height()*435/1080);
    connect(btnedit, &QPushButton::clicked, this, &HomeInterface::btneditClicked);

    /*QGridLayout *gl = new QGridLayout;
    gl->setColumnStretch(0, 100);
    gl->setColumnStretch(1, 100);
    gl->setColumnStretch(2, 100);
    gl->setRowStretch(0, 100);
    gl->setRowStretch(1, 100);
    gl->setRowStretch(2, 100);
    gl->addWidget(btnplay, 2, 0, 1, 1);
    gl->addWidget(btnedit, 2, 2, 1, 1);
    this->setLayout(gl);*/
}

HomeInterface::~HomeInterface(){}

void HomeInterface::paintEvent(QPaintEvent*){
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/home_background"));
}

void HomeInterface::resizeEvent(QResizeEvent *){
    btnplay->setGeometry(this->width()*64/1920, this->height()*312/1080, this->width()*617/1920, this->height()*435/1080);
    btnedit->setGeometry(this->width()*1060/1920, this->height()*312/1080, this->width()*617/1920, this->height()*435/1080);
    btnmatch->setGeometry(this->width()*716/1920, this->height()*312/1080, this->width()*306/1920, this->height()*435/1080);
}

void HomeInterface::btnplayClicked(){
    mw->switchstate(MainWindow::Waiting);
}

void HomeInterface::btneditClicked(){
    mw->switchstate(MainWindow::EditDeck);
}

void HomeInterface::btnmatchClicked(){
    mw->switchstate(MainWindow::Waiting);
}
