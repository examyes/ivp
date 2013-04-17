#ifndef OVERLAY_H
#define OVERLAY_H

#include <map>
#include <QMouseEvent>
using namespace std;

#include <QtWidgets/QWidget>

#include "MetaEntry.h"

class Overlay : public QWidget
{
    Q_OBJECT
public:
    Overlay(QWidget *parent = 0);
    ~Overlay();

protected:
    void mouseMoveEvent (QMouseEvent * event);
    void mouseReleaseEvent (QMouseEvent * event);

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
    void showEntry(MetaEntry* entry);
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

    map<MetaEntry*, QWidget*> boxes;

    int mouseX;
    int mouseY;

};

#endif
