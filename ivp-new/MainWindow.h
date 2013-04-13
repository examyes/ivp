#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "VideoPlayer.h"
#include "Overlay.h"
#include "SideBar.h"
#include "MetaItem.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public signals:
    /*
     * Emit this signal when user selected a file to open
     * Tell videoplayer to load the file
     * Tell metainfo to load xml file with same name
     */
    void openFile(QString filename);

public slots:
    void open();

protected:
    void createWidgets();
    void createActions();
    void createMenus();
    void createConnections();

private:
    QAction *openAction;
    QAction *exitAction;

    QMenu *fileMenu;

    VideoPlayer* videoPlayer;
    SideBar* sideBar;
    Overlay* overlay;
    MetaInfo* meta;

};

#endif // MAINWINDOW_H
