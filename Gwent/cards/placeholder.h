#ifndef PLACEHOLDER_H
#define PLACEHOLDER_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

class PlaceHolder : public QLabel
{
    Q_OBJECT
public:
    PlaceHolder(int index, QWidget *parent = nullptr);

    //void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

signals:
    void send_pressed(int index);

private:
    int index;
};

#endif // PLACEHOLDER_H
