#include "MetaEntry.h"

MetaEntry::MetaEntry(
            long long _timeStart,
            long long _timeStop,
            double _top,
            double _left,
            double _width,
            double _height,
            int _itemId
        ):
    timeStart(_timeStart),
    timeStop(_timeStop),
    top(_top),
    left(_left),
    width(_width),
    height(_height),
    itemId(_itemId){}

