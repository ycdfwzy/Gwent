#ifndef WAITINTERFACE_H
#define WAITINTERFACE_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>

class MainWindow;

class WaitInterface : public QWidget
{
    Q_OBJECT
public:
    explicit WaitInterface(MainWindow *mw_, QWidget *parent = nullptr);
    ~WaitInterface();
    QPushButton *stopbtn;
    MainWindow *mw;

    void stopbtnClicked();

signals:

public slots:

protected:
    void paintEvent(QPaintEvent*);
};

#endif // WAITINTERFACE_H
