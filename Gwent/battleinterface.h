#ifndef BATTLEINTERFACE_H
#define BATTLEINTERFACE_H

#include <QWidget>
#include <QScrollArea>
#include <QPainter>

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

private:
    QScrollArea *m_graveyard, *m_card, *m_melee, *m_ranged, *m_siege;
    QScrollArea *o_graveyard, *o_card, *o_melee, *o_ranged, *o_siege;
    // cards lists
};

#endif // BATTLEINTERFACE_H
