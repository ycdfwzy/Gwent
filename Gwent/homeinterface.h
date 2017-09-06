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
    QPushButton *btnplay, *btnedit, *btnmatch;

    void btnplayClicked();
    void btneditClicked();
    void btnmatchClicked();

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

signals:

public slots:
};

#endif // HOMEINTERFACE_H
