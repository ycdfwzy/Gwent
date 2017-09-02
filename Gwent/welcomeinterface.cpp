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
        createDialog();
        //QMessageBox::about(this, tr("mousepress"), tr("Press!"));
        //mw->mGameClient = new gameClient(mw);
    }
}

void WelcomeInterface::keyPressEvent(QKeyEvent *event){
    //qDebug() << event->key();
    if (event->key() == Qt::Key_Return){
        createDialog();
        //QMessageBox::about(this, tr("keypress"), tr("Press!"));
        //mw->mGameClient = new gameClient(mw);
    }
}

void WelcomeInterface::createDialog(){
    mdialog = new QDialog(this);
    mdialog->setWindowTitle(QObject::tr("Log in"));

    lbusername = new QLabel("Username:");
    ledtusername = new QLineEdit;

    lbpassword = new QLabel("Password:");
    ledtpassword = new QLineEdit;
    ledtpassword->setEchoMode(QLineEdit::Password);

    btnlogin = new QPushButton("Log in");
    connect(btnlogin, &QPushButton::clicked, this, &WelcomeInterface::tryconnect);

    QHBoxLayout *hbl1 = new QHBoxLayout;
    hbl1->addWidget(lbusername);
    hbl1->addWidget(ledtusername);

    QHBoxLayout *hbl2 = new QHBoxLayout;
    hbl2->addWidget(lbpassword);
    hbl2->addWidget(ledtpassword);

    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->addLayout(hbl1);
    vbl->addLayout(hbl2);
    vbl->addWidget(btnlogin);

    mdialog->setLayout(vbl);

    mdialog->exec();
}

void WelcomeInterface::tryconnect(){
    mw->mGameClient = new gameClient(mw);
}
