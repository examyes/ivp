#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>

class SideBar : public QScrollArea
{
    Q_OBJECT
public:
    explicit SideBar(QWidget *parent = 0);
    ~SideBar();
    QSize sizeHint() const;

signals:
    
public slots:

private:
    QLabel *text;
    QLabel *title;
};

#endif // SIDEBAR_H
