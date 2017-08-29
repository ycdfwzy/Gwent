#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mCurrentStateWidget(new Ui::MainWindow)
{
    //mCurrentStateWidget = new QWidget;
    mCurrentStateWidget->setupUi(this);

    connect(mCurrentStateWidget->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
    setWindowTitle(tr("Gwent"));
    this->resize(900, 600);
}

MainWindow::~MainWindow()
{
    delete mCurrentStateWidget;
}

void MainWindow::on_pushButton_clicked()
{
    this->resize(800, 600);
    //QMessageBox::about(this, "Mess", "Clicked");
}
