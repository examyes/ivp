#include "MetaInfo.h"

#include <QtXml>

MetaInfo::MetaInfo(){
    items.clear();
    entries.clear();
}

MetaInfo::~MetaInfo(){
}

void MetaInfo::seekTo(int millisecond){
    emit reset();
    beginIndex = 0;
    endIndex = 0;
    //playTo(millisecond);
    while (beginIndex < entries.size() && (entries.at(beginIndex))->timeStart <= millisecond)
        beginIndex ++;

    while (endIndex < entries.size() && (entries.at(endIndex))->timeStop <= millisecond)
        endIndex ++;

    for (int i = endIndex; i < beginIndex; i++)
        emit begin(entries.at(i));
}

void MetaInfo::playTo(int millisecond){
    while (beginIndex < entries.size() && (entries.at(beginIndex))->timeStart <= millisecond){
        emit begin(entries.at(beginIndex));
        beginIndex ++;
    }
    while (endIndex < entries.size() && (entries.at(endIndex))->timeStop <= millisecond){
        emit end(entries.at(endIndex));
        endIndex ++;
    }
}

void MetaInfo::select(MetaEntry *entry){
    int id = entry->itemId;
    emit show(items[id]);
}

void MetaInfo::open(QString filename){
    // remove existing items and entries
    for(map<int, MetaItem*>::iterator it= items.begin(); it!= items.end(); it++)
        delete (it->second);
    for(vector<MetaEntry*>::iterator it= entries.begin(); it!= entries.end(); it++)
        delete (*it);
    items.clear();
    entries.clear();

    // get xml file path
    QFileInfo info = QFileInfo(filename);
    QString path = info.filePath();
    QString name = info.completeBaseName();
    QString xmlFilename = path + name + ".xml";

    // test file exist
    QFileInfo xmlInfo(xmlFilename);
    if (!xmlInfo.exists()) return;

    // read xml file
    readXML(xmlFilename);

    // resetFlags
    beginIndex = 0;
    endIndex = 0;
}

void MetaInfo::readXML(QString filename){
    // create dom document
    QDomDocument doc("video meta info"); 

    // load file
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) return;
    if (!doc.setContent(&file)) { file.close(); return; }
    file.close();

    // parse items
    QDomNodeList itemNodes = doc.elementsByTagName("item");
    int itemCount = itemNodes.length();
    for (int i=0; i<itemCount; i++){
        QDomNode node = itemNodes.at(i);
        int id = node.attributes().namedItem("id").nodeValue().toInt();
        QString title, img, text;

        QDomNodeList children = node.childNodes();
        int childrenCount = children.length();
        for (int j=0; j<childrenCount; j++){
            QDomNode node = children.at(j);
            QString name = node.nodeName();
            if (name == "title") title = node.nodeValue();
            if (name == "img") img = node.nodeValue();
            if (name == "text") text = node.nodeValue();
        }

        MetaItem * item = new MetaItem(title, img, text);
        items[id] = item;
    }

    // parse entries
    QDomNodeList entryNodes = doc.elementsByTagName("entry");
    int entryCount = entryNodes.length();
    for (int i=0; i<entryCount; i++){
        QDomNode node = entryNodes.at(i);
        QString timestart = node.attributes().namedItem("timestart").nodeValue();
        QString timestop = node.attributes().namedItem("timestop").nodeValue();
        double top = node.attributes().namedItem("top").nodeValue().toDouble();
        double left = node.attributes().namedItem("top").nodeValue().toDouble();
        double width = node.attributes().namedItem("width").nodeValue().toDouble();
        double height = node.attributes().namedItem("height").nodeValue().toDouble();

        int id = node.nodeValue().toInt();

        MetaEntry* entry = new MetaEntry(parseTime(timestart),
                parseTime(timestop),
                top, left, width, height, id);

        entries.push_back(entry);
    }
}

int MetaInfo::parseTime(QString s){
    // convert time string to number of milliseconds
    // time format: h:m:s or h:m:s:ms
    QStringList list = s.split(':');
    int hour, minute, second, millisecond;

    hour = list.at(0).toInt();
    minute = list.at(1).toInt();
    second = list.at(2).toInt();
    if (list.count() > 3) millisecond = list.at(3).toInt();
    else millisecond = 0;

    return millisecond + ((hour * 60 + minute) * 60 + second) * 1000;
}
