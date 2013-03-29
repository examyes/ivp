#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videoplayer.h"
#include "sidebar.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    
public slots:
    void open();

protected:
    void createWidgets();
    void createActions();
    void createMenus();

private:
    QAction *openAction;

    QMenu *fileMenu;

    VideoPlayer *videoplayer;
    SideBar *sidebar;

};

#endif // MAINWINDOW_H
