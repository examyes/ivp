#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>

#include "MediaItem.h"

class SideBar : public QScrollArea
{
    Q_OBJECT
public:
    explicit SideBar(QWidget *parent = 0);
    ~SideBar();
    QSize sizeHint() const;


public slots:
    /*
     * Update information on the sidebar
     */
    void showItem(MediaItem* item);


private:
    QLabel *text;
    QLabel *title;
};

#endif // SIDEBAR_H
