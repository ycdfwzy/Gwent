#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include "welcomeinterface.h"
#include "gameclient.h"
/*
namespace Ui {
class MainWindow;
}
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    gameClient *mGameClient;
    enum GameState { Welcome, Playing, Replay, LastStand };

public slots:
    void switchstate(MainWindow:: GameState state);

private:
    GameState mGameState;
    QWidget *mCurrentStateWidget;

};

#endif // MAINWINDOW_H
