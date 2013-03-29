#ifndef FRAMEWIDGET_H
#define FRAMEWIDGET_H

#include <QPainter>
#include <QPen>
#include <QWidget>
#include <QtGui>

class FrameWidget : public QWidget
{
     Q_OBJECT

public:
     FrameWidget(QWidget *parent = 0);

protected:

    void paintEvent(QPaintEvent* event);


};

#endif
