#ifndef WELCOMEINTERFACE_H
#define WELCOMEINTERFACE_H

#include <QWidget>
#include <QPalette>
#include <QPixmap>
#include <QEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>

class MainWindow;

class WelcomeInterface : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeInterface(MainWindow *mw_, QWidget *parent = nullptr);
    ~WelcomeInterface();
    MainWindow *mw;

protected:
    void WelcomeInterface::paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:

public slots:

private:

};

#endif // WELCOMEINTERFACE_H
