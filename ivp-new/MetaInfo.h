#ifndef METAINFO_H
#define METAINFO_H

#include <vector>
#include <map>
using namespace std;

#include <QtWidgets/QWidget>

#include "MetaEntry.h"
#include "MetaItem.h"

class MetaInfo : public QObject
{
    Q_OBJECT
public:
    MetaInfo();
    ~MetaInfo();

public signals:
    /*
     * Emit begin if a new overlay box should appear at current playing position 
     */
    void begin(MetaEntry* entry);
    /*
     * Emit end if an existing overlay box should be removed at current playing position.
     */
    void end(MetaEntry* entry);
    /*
     * Emit reset to tell overlay to remove all boxes
     * When a seekTo happens, we might need to emit reset and emit several begins.
     */
    void reset();
    /*
     * Emit show to tell sidebar to show this item
     * Emit this signal in selected slot
     */
    void show(MetaItem* item);

public slots:
    /*
     * update current position,
     * emit reset signal, 
     * then emit begin for all meta entries that should be shown
     * at current position
     */
    void seekTo(int millisecond);
    /*
     * update current position,
     * emit begin and end signals if necessary
     */
    void playTo(int millisecond);
    /*
     * find the metaitem corresponding to this entry
     * and emit show signal
     */
    void select(MetaEntry* entry);
    /*
     * look for xml file with same filename,
     * load items and entries from it if exists
     */
    void open(QString filename);

private slots:

private:
    vector<MetaEntry*> entries;
    map<int, MetaItem*> items;

    void readXML(QString filename);
    int parseTime(QString time);

    int beginIndex, endIndex;
};

#endif
