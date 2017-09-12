#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mCurrentStateWidget = nullptr;
    mplayer = nullptr;
    //mGameClient = new gameClient(this);
    mGameClient = nullptr;
    this->switchstate(Welcome);
    this->setWindowTitle(tr("Gwent"));
    this->setWindowIcon(QIcon(QStringLiteral(":/images/icon")));
    this->resize(960, 600);
}

MainWindow::~MainWindow()
{
    delete mCurrentStateWidget;
}

void MainWindow::init_player(const QString &str){
    mplayer = new Player(mGameClient, str);
}

void MainWindow::switchstate(MainWindow::GameState state){
    if (mCurrentStateWidget == nullptr || mGameState != state){
        delete mCurrentStateWidget;
        mGameState = state;
        switch (state) {
        case Welcome:
            mCurrentStateWidget = new WelcomeInterface(this);
            this->setCentralWidget(mCurrentStateWidget);
            break;
        case Home:
            mCurrentStateWidget = new HomeInterface(this);
            this->setCentralWidget(mCurrentStateWidget);
            break;
        case Waiting:
            mCurrentStateWidget = new WaitBattleInterface(this);
            this->setCentralWidget(mCurrentStateWidget);
            break;
        case Playing:
            mCurrentStateWidget = new BattleInterface(this);
            this->setCentralWidget(mCurrentStateWidget);
            break;
        case GameOver:
            break;
        case EditDeck:
            mCurrentStateWidget = new EditDeckInterface(this);
            this->setMouseTracking(true);
            this->setCentralWidget(mCurrentStateWidget);
            break;
        case Choose:
            mCurrentStateWidget = new ChooseforBattleInterface(this);
            this->setMouseTracking(true);
            this->setCentralWidget(mCurrentStateWidget);
            break;
        default:
            break;
        }

    }
}

Player* MainWindow::get_player()const{return mplayer;}
void MainWindow::setoverbackground(int h){

}
