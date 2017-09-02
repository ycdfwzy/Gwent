#ifndef WELCOMEINTERFACE_H
#define WELCOMEINTERFACE_H

#include <QWidget>
#include <QPalette>
#include <QPixmap>
#include <QEvent>
#include <QPainter>

class WelcomeInterface : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeInterface(QWidget *parent = nullptr);
    ~WelcomeInterface();

    void WelcomeInterface::paintEvent(QPaintEvent *e);
signals:

public slots:
};

#endif // WELCOMEINTERFACE_H
