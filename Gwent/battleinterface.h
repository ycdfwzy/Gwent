#ifndef BATTLEINTERFACE_H
#define BATTLEINTERFACE_H

#include <QWidget>
#include <QScrollArea>
#include <QTextEdit>
#include <QLabel>
#include <QPainter>
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
    void resizeEvent(QResizeEvent*);

signals:

public slots:
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

private:
    QScrollArea *m_graveyard, *m_card, *m_melee, *m_ranged, *m_siege;
    QScrollArea *o_graveyard, *o_card, *o_melee, *o_ranged, *o_siege;
    QTextEdit *edt;
    ScoreLabel *m_meleescorelabel, *m_rangedscorelabel, *m_siegescorelabel, *m_totalscorelabel;
    ScoreLabel *o_meleescorelabel, *o_rangedscorelabel, *o_siegescorelabel, *o_totalscorelabel;
    ShowBattleCard *m_graveyardshow, *m_cardshow, *m_meleeshow, *m_rangedshow, *m_siegeshow;
    ShowBattleCard *o_graveyardshow, *o_cardshow, *o_meleeshow, *o_rangedshow, *o_siegeshow;
    // cards lists
};

#endif // BATTLEINTERFACE_H
