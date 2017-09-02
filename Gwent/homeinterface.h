#ifndef HOMEINTERFACE_H
#define HOMEINTERFACE_H

#include <QWidget>

class MainWindow;

class HomeInterface : public QWidget
{
    Q_OBJECT
public:
    explicit HomeInterface(MainWindow *mw_, QWidget *parent = nullptr);
    ~HomeInterface();
    MainWindow *mw;
signals:

public slots:
};

#endif // HOMEINTERFACE_H
