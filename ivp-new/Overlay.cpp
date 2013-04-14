#include "Overlay.h"

Overlay::Overlay(QWidget *parent):QWidget(parent){
}

Overlay::~Overlay(){
}

void Overlay::show(MetaEntry* entry){
    printf("Show %d\n", entry->itemId);
}

void Overlay::hide(MetaEntry* entry){
    printf("Hide %d\n", entry->itemId);
}

void Overlay::hideAll(){
    printf("Hide all");
}
