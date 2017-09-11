#include "placeholder.h"

PlaceHolder::PlaceHolder(int index, QWidget *parent) : QLabel(parent)
{
    this->index = index;
    this->setMouseTracking(true);
    this->setStyleSheet("background-color:transparent");
}
/*
void PlaceHolder::paintEvent(QPaintEvent *){
    //QPainter painter(this);
    //painter.

}
*/
void PlaceHolder::mousePressEvent(QMouseEvent *){
    emit send_pressed(index);
}
