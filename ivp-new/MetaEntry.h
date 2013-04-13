#ifndef METAENTRY_H
#define METAENTRY_H

class MetaEntry{

public:
    explicit MetaEntry(
            int _timeStart,
            int _timeStop,
            double _top,
            double _left,
            double _width,
            double _height,
            int _itemId
            );

    const int timeStart, timeStop;//in millisecond
    const double top, left, width, height;
    const int itemId;
}

#endif
