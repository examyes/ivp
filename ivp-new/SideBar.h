#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

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

private slots:
    void imageLoaded(QNetworkReply* reply);


private:
    QPushButton *hideButton;

    QLabel *text;
    QLabel *title;
    QLabel *image;
    QWidget *sidebarWidget;

    QNetworkAccessManager webCtrl;

    void loadImage(QString url);
};

#endif // SIDEBAR_H
