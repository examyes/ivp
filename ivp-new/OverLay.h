#ifndef OVERLAY_H
#define OVERLAY_H

#include <QtWidgets/QWidget>

#include "MetaEntry.h"

class Overlay : public QWidget
{
    Q_OBJECT
public:
    Overlay(QWidget *parent = 0);
    ~Overlay();

signals:
    /*
     * Emit clicked if an overlay box is clicked
     * to tell sidebar to update and show
     */
    void clicked(MetaEntry* entry);
    /*
     * Emit clickedBlank if a mouse click event is captured outside all boxes,
     * to tell sidebar to hide
     */
    void clickedBlank();

public slots:
    /*
     * add a new overlay box based on the entry
     */
    void show(MetaEntry* entry);
    /*
     * remove the overlay box showing the entry
     */
    void hide(MetaEntry* entry);
    /*
     * remove all overlay boxes
     */
    void hideAll();
    // might need to override resize

private slots:

private:

};

#endif
