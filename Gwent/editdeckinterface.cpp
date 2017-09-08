#include "editdeckinterface.h"
#include "mainwindow.h"
#include <QDebug>

//QString background[2] = {"", ""};

EditDeckInterface::EditDeckInterface(MainWindow *mw_, QWidget *parent) : QWidget(parent)
{
    mw = mw_;
    this->setMouseTracking(true);

    state = 0; // deckwindow
    decklist = mw->get_player()->get_decks_pointer();
    deckwindow = new QScrollArea(this);
    deckwindow->setStyleSheet("background-color:transparent");
    deckwindow->setGeometry(0, this->height()*240/1080, this->width(), this->height()*(900-240)/1080);

    scad = new ShowCardsAllDecks(decklist, this);
    scad->Resize(deckwindow->width(), deckwindow->height());
    connect(scad, SIGNAL(haschosen(int)), this, SLOT(ToCardState(int)));
    deckwindow->setWidget(scad);

    btnback = new QPushButton("Back", this);
    connect(btnback, &QPushButton::clicked, this, &EditDeckInterface::Backtohome);

    btnnew = new QPushButton("New Deck", this);
    connect(btnnew, &QPushButton::clicked, this, &EditDeckInterface::Toeditdecks);

    edt = nullptr;
}

void EditDeckInterface::Backtohome(){
    mw->switchstate(MainWindow::Home);
}

void EditDeckInterface::Toeditdecks(){
}

void EditDeckInterface::resizeEvent(QResizeEvent *){
    if (state == 0){
        deckwindow->setGeometry(0, this->height()*240/1080, this->width(), this->height()*(900-240)/1080);
        scad->Resize(deckwindow->width(), deckwindow->height());
        btnback->setGeometry(this->width()*70/192, this->height()*100/108, this->width()*20/192, this->height()*5/108);
        btnnew->setGeometry(this->width()*102/192, this->height()*100/108, this->width()*20/192, this->height()*5/108);
    } else
    {
        cardwindow_all->setGeometry(0, this->height()*24/108, this->width()*145/192, this->height()*33/108);
        scad->Resize(cardwindow_all->width(), cardwindow_all->height());

        cardwindow_deck->setGeometry(0, this->height()*57/108, this->width()*145/192, this->height()*33/108);
        scad->Resize(cardwindow_deck->width(), cardwindow_deck->height());

        btnsave->setGeometry(this->width()*70/192, this->height()*100/108, this->width()*20/192, this->height()*5/108);
        btnexit->setGeometry(this->width()*102/192, this->height()*100/108, this->width()*20/192, this->height()*5/108);

        if (edt != nullptr){
            edt->setGeometry(this->width()*150/192, this->width()*24/180, this->width()*47/192, this->height()*66/108);
        }
    }
}

void EditDeckInterface::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/images/editdeck"));
}

void EditDeckInterface::mouseMoveEvent(QMouseEvent *){
    if (state == 0){
        QList<CardLabelChooseDeck*> *tmp = scad->getcontains();
        int sz = tmp->size();
        for (int i = 0; i < sz; ++i){
            CardLabelChooseDeck* clcd = tmp->at(i);
            if (clcd->get_showmsg()){
                clcd->change_showmsg();
                clcd->update();
            }
        }
    } else
    {
        unshowcard();
    }
}

void EditDeckInterface::mousePressEvent(QMouseEvent *){

}

void EditDeckInterface::mouseResleaseEvent(QMouseEvent *){

}

void EditDeckInterface::ToCardState(int id){
    state = 1; //cardwindow
    delete btnback;
    delete btnnew;
    delete scad;
    delete deckwindow;
    deckwindow = nullptr;
    scad = nullptr;
    btnback = nullptr;
    btnnew = nullptr;

    cardwindow_all = new QScrollArea(this);
    scid_all = new ShowCardsInDeck(Deck::get_ALL(), this);
    scid_all->Resize(deckwindow->width(), deckwindow->height());
    connect(scid_all, SIGNAL(send_click(Card*)), this, SLOT(addonecard(Card*)));
    connect(scid_all, SIGNAL(send_hover(Card*)), this, SLOT(showcard(Card*)));

    Deck* tmp = decklist->at(id);
    scid_deck = new ShowCardsInDeck(tmp, this);
    scid_deck->Resize(deckwindow->width(), deckwindow->height());
    connect(scid_deck, SIGNAL(send_click(Card*)), this, SLOT(removeonecard(Card*)));
    connect(scid_deck, SIGNAL(send_hover(Card*)), this, SLOT(showcard(Card*)));

    btnsave = new QPushButton("Save&Exit", this);
    connect(btnsave, &QPushButton::clicked, this, &EditDeckInterface::Save_Exit);

    btnexit = new QPushButton("Exit", this);
    connect(btnexit, &QPushButton::clicked, this, &EditDeckInterface::Exit);
}

void EditDeckInterface::unshowcard(){
    delete edt;
    edt = nullptr;
}

void EditDeckInterface::showcard(Card* card_){
    edt = new QTextEdit;
    edt->setStyleSheet("background-color:transparent");
    edt->setTextColor(Qt::white);
    QString str = card_->get_name();
    str += "Base: " + QString::number(card_->get_baseblood()) + "\n";
    str += "Boost: " + QString::number(card_->get_boostblood()) + "\n";
    str += "Armor: " + QString::number(card_->get_armor()) + "\n";
    str += card_->get_rule() + "\n";
    str += card_->get_type() + "\n";
    edt->setText(str);
    edt->setReadOnly(true);
    //edt->wordWrapMode()
}

void EditDeckInterface::addonecard(Card* card_){
    scid_deck->addonecard(card_);
}

void EditDeckInterface::removeonecard(Card* card_){
    scid_deck->removecard(card_);
}

void EditDeckInterface::Save_Exit(){

}

void EditDeckInterface::Exit(){

}
