#ifndef EDITDECKINTERFACE_H
#define EDITDECKINTERFACE_H

#include <QWidget>

class MainWindow;

class EditDeckInterface : public QWidget
{
    Q_OBJECT
public:
    explicit EditDeckInterface(MainWindow *mw_, QWidget *parent = nullptr);

    MainWindow *mw;

signals:

public slots:
};

#endif // EDITDECKINTERFACE_H
