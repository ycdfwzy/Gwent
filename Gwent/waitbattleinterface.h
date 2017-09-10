#ifndef WAITINTERFACE_H
#define WAITINTERFACE_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QTimer>
#include <QLabel>
#include <QPropertyAnimation>

class MainWindow;

class WaitBattleInterface : public QWidget
{
    Q_OBJECT
public:
    explicit WaitBattleInterface(MainWindow *mw_, QWidget *parent = nullptr);
    ~WaitBattleInterface();

    MainWindow *mw;

    void stopbtnClicked();

signals:

public slots:
    void restartanimation();
    void hasfound();
    void startbattle();

protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);

private:
    QPushButton *stopbtn, *Slide;
    QPropertyAnimation *animation;
    QLabel *tips;
    QTimer *timer;
};

#endif // WAITINTERFACE_H
