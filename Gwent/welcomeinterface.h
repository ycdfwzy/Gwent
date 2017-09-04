#ifndef WELCOMEINTERFACE_H
#define WELCOMEINTERFACE_H

#include <QWidget>
#include <QPalette>
#include <QPixmap>
#include <QEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QLayout>

class MainWindow;

class WelcomeInterface : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeInterface(MainWindow *mw_, QWidget *parent = nullptr);
    ~WelcomeInterface();
    MainWindow *mw;
    void createDialog();
    void tryconnect();

protected:
    void WelcomeInterface::paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:

public slots:

private:
    QDialog *mdialog;
    QLineEdit *ledtusername, *ledtpassword;
    QLabel *lbusername, *lbpassword;
    QPushButton *btnlogin;
};

#endif // WELCOMEINTERFACE_H
