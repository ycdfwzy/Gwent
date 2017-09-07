#ifndef EDITDECKINTERFACE_H
#define EDITDECKINTERFACE_H

#include <QWidget>
#include <QListWidget>
#include <QPainter>

class MainWindow;

class EditDeckInterface : public QWidget
{
    Q_OBJECT
public:
    explicit EditDeckInterface(MainWindow *mw_, QWidget *parent = nullptr);

    MainWindow *mw;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

private:
    QListWidget *deckwindow;
};

#endif // EDITDECKINTERFACE_H
