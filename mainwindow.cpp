#include "mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createWidgets();
    createActions();
    createMenus();
}

MainWindow::~MainWindow(){

}

void MainWindow::createWidgets(){
    videoplayer = new VideoPlayer();
    sidebar = new SideBar();

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(videoplayer);
    layout->addWidget(sidebar);

    QWidget *window = new QWidget();
    window->setLayout(layout);

    setCentralWidget(window);

    setGeometry(100,100,900,500);

    sidebar->hide();
}

void MainWindow::createActions(){

}

void MainWindow::createMenus(){

}


void MainWindow::open()
{
    //errorLabel->setText("");

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());

    videoplayer->openFile(fileName);
}

