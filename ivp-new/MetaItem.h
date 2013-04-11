#ifndef METAITEM_H
#define METAITEM_H

class MetaItem{

public:
    explicit MetaItem(
            QString _title,
            QString _imgURL,
            QString _text);

    const QString title, imgURL, text;
}

#endif
