#ifndef BATTLEINTERFACE_H
#define BATTLEINTERFACE_H

#include <QWidget>
#include <QScrollArea>
#include <QTextEdit>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QMessageBox>
#include "scorelabel.h"
#include "cards/showbattlecard.h"

class MainWindow;

class BattleInterface : public QWidget
{
    Q_OBJECT
public:
    explicit BattleInterface(MainWindow *mw_, QWidget *parent = nullptr);

    MainWindow *mw;

    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);
    void resizeEvent(QResizeEvent*);

    void layout_score();

    void loaddeck(int, QString);
    void pump(int, int);
    void Mulligantips(int);
    void roundstarttips(int);
    void roundendtips(int);
    void turntip(int);
    void move(QString);
    void bloodchange(QString);
    //void move(ShowBattleCard* src, int srcid, ShowBattleCard* tar, int tarid = -1);
    void move(int, int, int, int j2 = -1);
    void updatescore();
    void gameover(int);
    //ShowBattleCard * convert(QString, int type = 0);

    void showcardinfo(Card*);
    void unshowcardinfo();
    enum SKY{clean=0, fog=1, frost=2, rain=3};

signals:

public slots:
    void receive_press_blank(int, int);
    void receive_press_card(int, int);
    void receive_hover_card(int, int);
    void send_surrender();
    void send_pass();

private:
    //01 手牌 23 攻城 45 远程 67 进程 89墓地 10 11卡组
    QScrollArea *qsa[12];
    //QScrollArea *m_graveyard, *m_card, *m_melee, *m_ranged, *m_siege;
    //QScrollArea *o_graveyard, *o_card, *o_melee, *o_ranged, *o_siege;
    QTextEdit *edt;
    ScoreLabel *scoreLabel[12];
    //ScoreLabel *m_meleescorelabel, *m_rangedscorelabel, *m_siegescorelabel, *m_totalscorelabel;
    //ScoreLabel *o_meleescorelabel, *o_rangedscorelabel, *o_siegescorelabel, *o_totalscorelabel;
    ShowBattleCard *shows[12];
    //ShowBattleCard *m_deckshow, *m_graveyardshow, *m_cardshow, *m_meleeshow, *m_rangedshow, *m_siegeshow;
    //ShowBattleCard *o_deckshow, *o_graveyardshow, *o_cardshow, *o_meleeshow, *o_rangedshow, *o_siegeshow;
    QLabel *turnlabel;
    QPushButton *btnpass, *btnsurrender;
    int score[2];
    SKY sky[12];
    // cards lists
};

#endif // BATTLEINTERFACE_H
