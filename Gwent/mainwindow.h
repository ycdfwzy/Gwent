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

public slots:
    void switchstate(MainWindow:: GameState state);

private:
    GameState mGameState;
    QWidget *mCurrentStateWidget;
    Player *mplayer;
    QString overbackground;

};

#endif // MAINWINDOW_H
