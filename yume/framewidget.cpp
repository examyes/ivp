#include "framewidget.h"

FrameWidget::FrameWidget(QWidget *parent):QWidget(parent) {

    setPalette(Qt::transparent);
  //  setAttribute(Qt::WA_TransparentForMouseEvents);
    resize(600, 400);
}

void FrameWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(QColor(255,0,0));
    painter.drawRect(0, 0, 100, 100);

    painter.drawRect(100, 100, 100, 100);
}
