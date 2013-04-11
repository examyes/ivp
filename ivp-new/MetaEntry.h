#ifndef METAENTRY_H
#define METAENTRY_H

class MetaEntry{

public:
    explicit MetaEntry(
            long long _timeStart,
            long long _timeStop,
            double _top,
            double _left,
            double _width,
            double _height,
            int _itemId
            );

    const long long timeStart, timeStop;//in millisecond
    const double top, left, width, height;
    const int itemId;
}

#endif
