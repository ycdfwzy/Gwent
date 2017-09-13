#ifndef GAMEOVERINTERFACE_H
#define GAMEOVERINTERFACE_H

#include <QWidget>
#include <QPushButton>

class MainWindow;

class GameoverInterface : public QWidget
{
    Q_OBJECT
public:
    explicit GameoverInterface(MainWindow *mw_, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);

signals:

public slots:
    void back_home();

private:
    MainWindow *mw;
    QPushButton *btnexit;
};

#endif // GAMEOVERINTERFACE_H
