#include "Overlay.h"

Overlay::Overlay(QWidget *parent):QWidget(parent){
    boxes.clear();
    this->setMouseTracking(true);
}

Overlay::~Overlay(){
}

void Overlay::showEntry(MetaEntry* entry){

    QWidget *box = new QWidget(this);

    // background color
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, QColor(255, 0, 0, 70));
    box->setAutoFillBackground(true);
    box->setPalette(Pal);

    // calculate size
    int w = this->size().width(), h = this->size().height();
    int boxW = entry->width * w, boxH = entry->height * h, boxX = entry->left * w, boxY = entry->top * h;

    // set position
    box->setGeometry(boxX, boxY, boxW, boxH);

    if(mouseX >= boxX && mouseX <= boxX+boxW)
        if(mouseY >= boxY && mouseY <= boxY+boxH)
            box->show();

    boxes[entry] = box;

    printf("Show %d\n", entry->itemId);
    printf("box %d %d %d %d\n", boxX, boxY, boxW, boxH);
}

void Overlay::hide(MetaEntry* entry){

    QWidget *box = boxes[entry];
    delete box;
    boxes.erase(entry);

    printf("Hide %d\n", entry->itemId);
}

void Overlay::hideAll(){

    for(map<MetaEntry*, QWidget*>::iterator it= boxes.begin(); it!= boxes.end(); it++)
        delete (it->second);
    boxes.clear();

    printf("Hide all\n");
}

void Overlay::mouseMoveEvent ( QMouseEvent * event ) {
    mouseX = event->x();
    mouseY = event->y();
}

