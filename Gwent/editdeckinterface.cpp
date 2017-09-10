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
    deckwindow->horizontalScrollBarPolicy();
    deckwindow->setStyleSheet("background-color:transparent");
    deckwindow->setGeometry(0, this->height()*240/1080, this->width(), this->height()*(900-240)/1080);

    scad = new ShowCardsAllDecks(decklist, this);
    scad->Resize(deckwindow->width(), deckwindow->height());
    connect(scad, SIGNAL(haschosen(int)), this, SLOT(ToCardState(int)));
    deckwindow->setWidget(scad);

    btnback = new QPushButton(this);
    btnback->setStyleSheet("border-image: url(:/images/btnexit)");
    connect(btnback, &QPushButton::clicked, this, &EditDeckInterface::Backtohome);

    btnnew = new QPushButton(this);
    btnnew->setStyleSheet("border-image: url(:/images/btnnew)");
    connect(btnnew, &QPushButton::clicked, this, &EditDeckInterface::Toeditdecks);

    cardwindow_all = new QScrollArea(this);
    cardwindow_all->setVisible(false);
    cardwindow_all->setStyleSheet("background-color:transparent");
    cardwindow_all->setGeometry(0, this->height()*24/108, this->width()*145/192, this->height()*33/108);

    scid_all = new ShowCardsInDeck(Deck::get_ALL(), this);
    scid_all->setVisible(false);
    scid_all->Resize(cardwindow_all->width(), cardwindow_all->height());
    connect(scid_all, SIGNAL(send_click(Card*)), this, SLOT(addonecard(Card*)));
    connect(scid_all, SIGNAL(send_hover(Card*)), this, SLOT(showcard(Card*)));
    cardwindow_all->setWidget(scid_all);

    cardwindow_deck = new QScrollArea(this);
    cardwindow_deck->setVisible(false);
    cardwindow_deck->setStyleSheet("background-color:transparent");
    cardwindow_deck->setGeometry(0, this->height()*57/108, this->width()*145/192, this->height()*33/108);

    scid_deck = new ShowCardsInDeck(this);
    scid_deck->setVisible(false);
    scid_deck->Resize(cardwindow_deck->width(), cardwindow_deck->height());
    connect(scid_deck, SIGNAL(send_click(Card*)), this, SLOT(removeonecard(Card*)));
    connect(scid_deck, SIGNAL(send_hover(Card*)), this, SLOT(showcard(Card*)));
    cardwindow_deck->setWidget(scid_deck);

    btnsave = new QPushButton(this);
    btnsave->setVisible(false);
    btnsave->setStyleSheet("border-image: url(:/images/btnsave)");
    connect(btnsave, &QPushButton::clicked, this, &EditDeckInterface::Save_Exit);

    btnexit = new QPushButton(this);
    btnexit->setVisible(false);
    btnexit->setStyleSheet("border-image: url(:/images/btnexit)");
    connect(btnexit, &QPushButton::clicked, this, &EditDeckInterface::Exit);

    edt = new QTextEdit(this);
    edt->setStyleSheet("background-color:transparent;border: none;");
    edt->setTextColor(Qt::white);
    edt->setReadOnly(true);
    edt->setVisible(false);
}

void EditDeckInterface::Backtohome(){
    mw->switchstate(MainWindow::Home);
}

void EditDeckInterface::Toeditdecks(){
    choose = 0;
    chooseleader = new QDialog();
    chooseleader->setFixedSize(220*2, 142*2);
    QPushButton *btn1 = new QPushButton(chooseleader);
    btn1->setStyleSheet("border-image: url(:/cards/cards/images/da2gang1.png)");
    btn1->setGeometry(0, 0, 100*2, 142*2);

    connect(btn1, SIGNAL(clicked(bool)), this, SLOT(dochoice1()));
    QPushButton *btn2 = new QPushButton(chooseleader);
    btn2->setStyleSheet("border-image: url(:/cards/cards/images/an4ying3zhang3zhe3.png)");
    connect(btn2, SIGNAL(clicked(bool)), this, SLOT(dochoice2()));
    btn2->setGeometry(120*2, 0, 100*2, 142*2);

    chooseleader->exec();

    if (choose != 1 && choose != 2)
        return;

    Deck* tmp;
    int t = mw->get_player()->get_nextdeckname();
    QString str = "Deck#" + QString::number(t);
    if (choose == 1){
        //qDebug() << 1;
        tmp = new Deck(str, new Card(183));
    } else
    if (choose == 2){
        //qDebug() << 2;
        tmp = new Deck(str, new Card(166));
    }

    state = 1;
    deckwindow->setVisible(false);
    scad->setVisible(false);
    btnback->setVisible(false);
    btnnew->setVisible(false);

    cardwindow_all->setVisible(true);
    scid_all->setVisible(true);
    cardwindow_deck->setVisible(true);
    btnsave->setVisible(true);
    btnexit->setVisible(true);

    scid_deck->changeDeck(tmp);
    scid_deck->Resize(cardwindow_deck->width(), cardwindow_deck->height());
    scid_deck->setVisible(true);
}

void EditDeckInterface::dochoice1(){ choose = 1; chooseleader->close(); }
void EditDeckInterface::dochoice2(){ choose = 2; chooseleader->close(); }

void EditDeckInterface::resizeEvent(QResizeEvent *){
    //if (state == 0){
        deckwindow->setGeometry(0, this->height()*240/1080, this->width(), this->height()*(900-240)/1080);
        scad->Resize(deckwindow->width(), deckwindow->height());
        btnback->setGeometry(this->width()*70/192, this->height()*100/108, this->width()*20/192, this->height()*5/108);
        btnnew->setGeometry(this->width()*102/192, this->height()*100/108, this->width()*20/192, this->height()*5/108);
    //} else
    //{
        cardwindow_all->setGeometry(0, this->height()*24/108, this->width()*145/192, this->height()*33/108);
        scid_all->Resize(cardwindow_all->width(), cardwindow_all->height());

        cardwindow_deck->setGeometry(0, this->height()*57/108, this->width()*145/192, this->height()*33/108);
        scid_deck->Resize(cardwindow_deck->width(), cardwindow_deck->height());

        btnsave->setGeometry(this->width()*70/192, this->height()*100/108, this->width()*20/192, this->height()*5/108);
        btnexit->setGeometry(this->width()*102/192, this->height()*100/108, this->width()*20/192, this->height()*5/108);

        edt->setGeometry(this->width()*150/192, this->width()*24/180, this->width()*47/192, this->height()*66/108);
    //}
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
    //qDebug() << id;
    state = 1;

    deckwindow->setVisible(false);
    scad->setVisible(false);
    btnback->setVisible(false);
    btnnew->setVisible(false);

    cardwindow_all->setVisible(true);
    scid_all->setVisible(true);
    cardwindow_deck->setVisible(true);
    btnsave->setVisible(true);
    btnexit->setVisible(true);

    Deck* tmp = decklist->at(id);
    scid_deck->changeDeck(tmp);
    //qDebug() << tmp->get_cards_pointer()->size();
    scid_deck->Resize(cardwindow_deck->width(), cardwindow_deck->height());
    scid_deck->setVisible(true);
}

void EditDeckInterface::unshowcard(){
    //delete edt;
    //edt = nullptr;
    edt->setVisible(false);
}

void EditDeckInterface::showcard(Card* card_){
    edt->setVisible(true);
    QString str = card_->get_name() + "\n";
    if (card_->get_baseblood() > 0){
        str += "Blood: " + QString::number(card_->get_baseblood()) + "\n";
    }
    //str += "Boost: " + QString::number(card_->get_boostblood()) + "\n";
    //str += "Armor: " + QString::number(card_->get_armor()) + "\n";
    str += card_->get_rule() + "\n";
    str += card_->get_type() + "\n";
    edt->setText(str);
}

void EditDeckInterface::addonecard(Card* card_){
    scid_deck->addonecard(card_);
    scid_deck->Resize(cardwindow_deck->width(), cardwindow_deck->height());
    //scid_deck->setVisible(true);
}

void EditDeckInterface::removeonecard(Card* card_){
    scid_deck->removecard(card_);
    scid_deck->Resize(cardwindow_deck->width(), cardwindow_deck->height());
    //scid_deck->setVisible(true);
}

void EditDeckInterface::Save_Exit(){
    QList<Card*> *tmp = scid_deck->get_cardlist();
    int sz = tmp->size();
    if (sz < 25){
        QMessageBox::critical(mw, QObject::tr("Error"), QObject::tr("Please make sure that your cards in this deck is not less than 25!"));
        return;
    }
    if (sz > 40){
        QMessageBox::critical(mw, QObject::tr("Error"), QObject::tr("Please make sure that your cards in this deck is not more than 40!"));
        return;
    }
    int goldcnt = 0, silvercnt = 0;
    for (int i = 0; i < sz; ++i){
        Card* t = tmp->at(i);
        QString col = t->get_color();
        if (col.compare("gold") == 0)
            ++goldcnt;
        if (col.compare("silver") == 0)
            ++silvercnt;
    }
    if (goldcnt > 4){
        QMessageBox::critical(mw, QObject::tr("Error"), QObject::tr("Please make sure that your gold cards in this deck is not more than 4!"));
        return;
    }
    if (silvercnt > 6){
        QMessageBox::critical(mw, QObject::tr("Error"), QObject::tr("Please make sure that your silver cards in this deck is not more than 6!"));
        return;
    }

    //bool flag =
    mw->get_player()->update_deck(scid_deck->get_name(), scid_deck->get_leader(), scid_deck->get_cardlist());
    decklist = mw->get_player()->get_decks_pointer();
    scad->update_deckslist(decklist);
    scad->Resize(deckwindow->width(), deckwindow->height());
    Exit();
}

void EditDeckInterface::Exit(){
    cardwindow_all->setVisible(false);
    //qDebug() << "cardwindow_all";
    scid_all->setVisible(false);
    //qDebug() << "scid_all";
    cardwindow_deck->setVisible(false);
    //qDebug() << "cardwindow_deck";
    scid_deck->setVisible(false);
    //qDebug() << "scid_deck";
    btnsave->setVisible(false);
    //qDebug() << "btnsave";
    btnexit->setVisible(false);
    //qDebug() << "btnexit";

    deckwindow->setVisible(true);
    //qDebug() << "deckwindow";
    scad->setVisible(true);
    //qDebug() << "scad";
    btnback->setVisible(true);
    //qDebug() << "btnback";
    btnnew->setVisible(true);
    //qDebug() << "btnnew";
}
