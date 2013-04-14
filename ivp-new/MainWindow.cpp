#include "MainWindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {

    meta = new MetaInfo();
    createWidgets();
    createActions();
    createMenus();
    createConnections();
}

MainWindow::~MainWindow(){

}

void MainWindow::createWidgets(){
    overlay = new Overlay();
    videoPlayer = new VideoPlayer(0, overlay);
    sideBar = new SideBar();

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(videoPlayer);
    layout->addWidget(sideBar);

    QWidget *window = new QWidget();
    window->setLayout(layout);

    setCentralWidget(window);

    setGeometry(100,100,900,500);

    sideBar->hide();
}

void MainWindow::createActions(){
    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(tr("Ctrl+O"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
}


void MainWindow::open() {

    QString filename = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());

    if (!filename.isEmpty())
        emit openFile(filename);
}

void MainWindow::createConnections(){
    connect(this, SIGNAL(openFile(QString)), videoPlayer, SLOT(open(QString)));
    connect(this, SIGNAL(openFile(QString)), meta, SLOT(open(QString)));


    connect(meta, SIGNAL(begin(MetaEntry*)), overlay, SLOT(show(MetaEntry*)));
    connect(meta, SIGNAL(end(MetaEntry*)), overlay, SLOT(hide(MetaEntry*)));
    connect(meta, SIGNAL(reset()), overlay, SLOT(hideAll()));


    connect(meta, SIGNAL(show(MetaItem*)), sideBar, SLOT(showItem(MetaItem*)));

    connect(overlay, SIGNAL(clicked(MetaEntry*)), meta, SLOT(select(MetaEntry*)));
    connect(overlay, SIGNAL(clickedBlank()), sideBar, SLOT(hide()));

    connect(videoPlayer, SIGNAL(playTo(int)), meta, SLOT(playTo(int)));
    connect(videoPlayer, SIGNAL(seekTo(int)), meta, SLOT(seekTo(int)));
}
