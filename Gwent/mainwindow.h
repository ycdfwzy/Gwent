#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include "welcomeinterface.h"
#include "gameclient.h"
#include "homeinterface.h"
#include "waitbattleinterface.h"
#include "editdeckinterface.h"
#include "chooseforbattleinterface.h"
#include "battleinterface.h"
#include "player.h"
#include "gameoverinterface.h"
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
    enum GameState { Welcome, Home, Waiting, Playing, GameOver, EditDeck, Choose};

    void init_player(const QString &str);
    Player* get_player()const;
    void setoverbackground(int h);
    QString get_overbackground();

public slots:
    void switchstate(MainWindow:: GameState state);

private:
    GameState mGameState;
    QWidget *mCurrentStateWidget;
    Player *mplayer;
    QString overbackground;
    QString picpath;
};

#endif // MAINWINDOW_H
