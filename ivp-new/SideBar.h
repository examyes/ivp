#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "MetaItem.h"

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
    void showItem(MetaItem* item);


private:
    QPushButton *hideButton;

    QLabel *text;
    QLabel *title;
    QWidget *sidebarWidget;
};

#endif // SIDEBAR_H
