#include "editdeckinterface.h"
#include "mainwindow.h"
#include <QDebug>

EditDeckInterface::EditDeckInterface(MainWindow *mw_, QWidget *parent) : QWidget(parent)
{
    mw = mw_;
    decklist = mw->get_player()->get_decks_pointer();
    //qDebug() << decklist->size();

    deckwindow = new QScrollArea(this);
    //deckwindow->setViewMode(QListView::IconMode);
    //deckwindow->setFlow(QListView::LeftToRight);
    deckwindow->setStyleSheet("background-color:transparent");
    deckwindow->setGeometry(0, this->height()*240/1080, this->width(), this->height()*(900-240)/1080);

    QList<Card*> cardlist;

    foreach (Deck* dk, *decklist){
        cardlist.append(dk->get_leader());
    }
    //qDebug() << cardlist.size();
    sc = new ShowCards(cardlist, this);
    sc->Resize(deckwindow->width(), deckwindow->height());
    deckwindow->setWidget(sc);
}

void EditDeckInterface::resizeEvent(QResizeEvent *){
    deckwindow->setGeometry(0, this->height()*240/1080, this->width(), this->height()*(900-240)/1080);
    sc->Resize(deckwindow->width(), deckwindow->height());
}

void EditDeckInterface::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/images/editdeck"));
}
