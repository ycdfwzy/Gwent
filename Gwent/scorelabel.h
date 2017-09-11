#ifndef SCORELABEL_H
#define SCORELABEL_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel>

class ScoreLabel : public QLabel
{
    Q_OBJECT
public:
    ScoreLabel(int score_, QWidget *parent = nullptr);

    int get_score();
    void set_score(int);
    void paintEvent(QPaintEvent*);

private:
    int score;
    static QString digit[10];
};

#endif // SCORELABEL_H
