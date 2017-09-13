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
    //void replace(QString);
    /*
    void loaddeck_m(QString);//加载牌组
    void loaddeck_o(QString);
    void pump_m(int);//抽卡
    void pump_o(int);
    void Mulligantips(int);//提示调度
    void roundstarttips(int);//提示一轮开始
    void roundendtips(int);//提示一轮结束
    void turntip(int);//提示回合
    void move_m(QString);//移动
    void move_o(QString);
    void replace_m(QString);//调度
    void replace_o(QString);
    */

    //void move(ShowBattleCard* src, int srcid, ShowBattleCard* tar, int tarid = -1);
    void move(int, int, int, int j2 = -1);
    void updatescore();
    void gameover(int);
    //ShowBattleCard * convert(QString, int type = 0);

    void showcardinfo(Card*);
    void unshowcardinfo();

signals:

public slots:
    /*
    void receive_press_card_m_card(int);
    void receive_press_card_m_melee(int);
    void receive_press_card_m_ranged(int);
    void receive_press_card_m_siege(int);
    void receive_press_card_o_card(int);
    void receive_press_card_o_melee(int);
    void receive_press_card_o_ranged(int);
    void receive_press_card_o_siege(int);

    void receive_hover_card_m_card(int);
    void receive_hover_card_m_melee(int);
    void receive_hover_card_m_ranged(int);
    void receive_hover_card_m_siege(int);
    void receive_hover_card_o_card(int);
    void receive_hover_card_o_melee(int);
    void receive_hover_card_o_ranged(int);
    void receive_hover_card_o_siege(int);

    void receive_press_blank_m_card(int);
    void receive_press_blank_m_melee(int);
    void receive_press_blank_m_ranged(int);
    void receive_press_blank_m_siege(int);
    void receive_press_blank_o_card(int);
    void receive_press_blank_o_melee(int);
    void receive_press_blank_o_ranged(int);
    void receive_press_blank_o_siege(int);
    */
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
    // cards lists
};

#endif // BATTLEINTERFACE_H
