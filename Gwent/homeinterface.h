#ifndef HOMEINTERFACE_H
#define HOMEINTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QLayout>

class MainWindow;
/*
class MyPushButton : public QPushButton{
    Q_OBJECT
public:
    MyPushButton();
    ~MyPushButton();

protected:
    void paintEvent(QPaintEvent*);
};
*/
class HomeInterface : public QWidget
{
    Q_OBJECT
public:
    explicit HomeInterface(MainWindow *mw_, QWidget *parent = nullptr);
    ~HomeInterface();
    MainWindow *mw;
    QPushButton *btnplay, *btnchoose;

    void btnplayClicked();
    void btnchooseClicked();

protected:
    void paintEvent(QPaintEvent*);


signals:

public slots:
};

#endif // HOMEINTERFACE_H
