#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mCurrentStateWidget = nullptr;
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
        case Playing:
            break;
        default:
            break;
        }
    }
}
