#include "homeinterface.h"
#include "mainwindow.h"

HomeInterface::HomeInterface(MainWindow *mw_, QWidget *parent) : QWidget(parent)
{
    mw = mw_;

}

HomeInterface::~HomeInterface(){}
