#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum GameState { Welcome, Playing, Replay, LastStand };

public slots:
    void on_pushButton_clicked();

private:
    GameState mGameState;
    Ui::MainWindow *mCurrentStateWidget;
};

#endif // MAINWINDOW_H
