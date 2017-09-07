#include "editdeckinterface.h"
#include "mainwindow.h"

EditDeckInterface::EditDeckInterface(MainWindow *mw_, QWidget *parent) : QWidget(parent)
{
    mw = mw_;

    deckwindow = new QListWidget(this);
    deckwindow->setViewMode(QListView::IconMode);
    deckwindow->setFlow(QListView::LeftToRight);
    deckwindow->setStyleSheet("background-color:transparent");

    deckwindow->setGeometry(0, this->height()*240/1080, this->width(), this->height()*(900-240)/1080);

    QListWidgetItem *w = new QListWidgetItem(deckwindow);
    w->setIcon(QIcon());
}

void EditDeckInterface::resizeEvent(QResizeEvent *){
    deckwindow->setGeometry(0, this->height()*240/1080, this->width(), this->height()*(900-240)/1080);
}

void EditDeckInterface::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/images/editdeck"));
}
