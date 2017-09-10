#include "chooseforbattleinterface.h"
#include "mainwindow.h"

ChooseforBattleInterface::ChooseforBattleInterface(MainWindow *mw_, QWidget *parent) : QWidget(parent)
{
    mw = mw_;
    this->setMouseTracking(true);
    decklist = mw->get_player()->get_decks_pointer();

    deckwindow = new QScrollArea(this);
    deckwindow->horizontalScrollBarPolicy();
    deckwindow->setStyleSheet("background-color:transparent");
    deckwindow->setGeometry(0, this->height()*240/1080, this->width(), this->height()*(900-240)/1080);

    scad = new ShowCardsAllDecks(decklist, this);
    scad->Resize(deckwindow->width(), deckwindow->height());
    connect(scad, SIGNAL(haschosen(int)), this, SLOT(dochoice(int)));
    deckwindow->setWidget(scad);
}

void ChooseforBattleInterface::dochoice(int id){
    QString str = "ChooseforBattle: " + decklist->at(id)->get_name();
    mw->mGameClient->Send_Date(str);
    mw->switchstate(MainWindow::Waiting);
}

void ChooseforBattleInterface::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/images/editdeck"));
}

void ChooseforBattleInterface::resizeEvent(QResizeEvent *){
    deckwindow->setGeometry(0, this->height()*240/1080, this->width(), this->height()*(900-240)/1080);
    scad->Resize(deckwindow->width(), deckwindow->height());
}

void ChooseforBattleInterface::mouseMoveEvent(QMouseEvent *){
    QList<CardLabelChooseDeck*> *tmp = scad->getcontains();
    int sz = tmp->size();
    for (int i = 0; i < sz; ++i){
        CardLabelChooseDeck* clcd = tmp->at(i);
        if (clcd->get_showmsg()){
            clcd->change_showmsg();
            clcd->update();
        }
    }
}
