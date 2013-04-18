#include "MetaInfo.h"

#include <QtXml>

struct compareBegin {
    inline bool operator() (const MetaEntry* entry1, const MetaEntry* entry2) {
        return (entry1->timeStart < entry2->timeStart);
    }
};

struct compareEnd {
    inline bool operator() (const MetaEntry* entry1, const MetaEntry* entry2) {
        return (entry1->timeStop < entry2->timeStop);
    }
};

MetaInfo::MetaInfo(){
    items.clear();
    entriesSortedBegin.clear();
    entriesSortedEnd.clear();
}

MetaInfo::~MetaInfo(){
}

void MetaInfo::seekTo(int millisecond){
    emit reset();
    beginIndex = 0;
    endIndex = 0;
    playTo(millisecond);
    /*
    while (beginIndex < entriesSortedBegin.size() && (entriesSortedBegin.at(beginIndex))->timeStart <= millisecond)
        beginIndex ++;

    while (endIndex < entriesSortedEnd.size() && (entriesSortedEnd.at(endIndex))->timeStop <= millisecond)
        endIndex ++;

    for (int i = endIndex; i < beginIndex; i++)
        emit begin(entries.at(i));
    */
}

void MetaInfo::playTo(int millisecond){
    //printf("Play to %d\n", millisecond);
    while (beginIndex < entriesSortedBegin.size() && (entriesSortedBegin.at(beginIndex))->timeStart <= millisecond){
        emit begin(entriesSortedBegin.at(beginIndex));
        beginIndex ++;
    }
    while (endIndex < entriesSortedEnd.size() && (entriesSortedEnd.at(endIndex))->timeStop <= millisecond){
        emit end(entriesSortedEnd.at(endIndex));
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
    for(vector<MetaEntry*>::iterator it= entriesSortedBegin.begin(); it!= entriesSortedBegin.end(); it++)
        delete (*it);
    for(vector<MetaEntry*>::iterator it= entriesSortedEnd.begin(); it!= entriesSortedEnd.end(); it++)
        delete (*it);
    items.clear();
    entriesSortedBegin.clear();
    entriesSortedEnd.clear();

    // get xml file path
    QFileInfo info = QFileInfo(filename);
    QDir dir = info.dir();
    QString name = info.completeBaseName();
    QString xmlFilename = name + ".xml";

    // test file exist
    QFileInfo xmlInfo(dir, xmlFilename);
    if (!xmlInfo.exists()){
        printf("File not there\n");
        printf("Filename: %s\n", xmlFilename.toStdString().c_str());
        return;
    }

    // read xml file
    readXML(xmlInfo.filePath());

    // resetFlags
    beginIndex = 0;
    endIndex = 0;
}

void MetaInfo::readXML(QString filename){
    printf("Read XML File: %s\n", filename.toStdString().c_str());
    // create dom document
    QDomDocument doc("video meta info"); 

    // load file
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)){
        printf("Cannot open file for reading\n");
        return;
    }
    if (!doc.setContent(&file)) {
        printf("Cannot setContent\n");
        file.close(); return; 
    }
    file.close();

    // parse items
    QDomNodeList itemNodes = doc.elementsByTagName("item");
    int itemCount = itemNodes.length();
    printf("%d items\n", itemCount);
    for (int i=0; i<itemCount; i++){
        QDomNode node = itemNodes.at(i);
        int id = node.attributes().namedItem("id").nodeValue().toInt();
        QString title, img, text;

        QDomNodeList children = node.childNodes();
        int childrenCount = children.length();
        for (int j=0; j<childrenCount; j++){
            QDomNode node = children.at(j);
            QString name = node.nodeName();
            if (name == "title") title = node.toElement().text();
            if (name == "img") img = node.toElement().text();
            if (name == "text") text = node.toElement().text();
        }

        MetaItem * item = new MetaItem(title, img, text);
        items[id] = item;
        printf("Item %s\n", title.toStdString().c_str());
    }

    // parse entries
    QDomNodeList entryNodes = doc.elementsByTagName("entry");
    int entryCount = entryNodes.length();
    printf("%d entries\n", entryCount);
    for (int i=0; i<entryCount; i++){
        QDomNode node = entryNodes.at(i);
        QString timestart = node.attributes().namedItem("timestart").nodeValue();
        QString timestop = node.attributes().namedItem("timestop").nodeValue();
        double top = node.attributes().namedItem("top").nodeValue().toDouble();
        double left = node.attributes().namedItem("left").nodeValue().toDouble();
        double width = node.attributes().namedItem("width").nodeValue().toDouble();
        double height = node.attributes().namedItem("height").nodeValue().toDouble();

        int id = node.toElement().text().toInt();

        MetaEntry* entry = new MetaEntry(parseTime(timestart),
                parseTime(timestop),
                top, left, width, height, id);

        entriesSortedBegin.push_back(entry);
        entriesSortedEnd.push_back(entry);
        printf("Entry %d: %s-%s\n", id, timestart.toStdString().c_str(),timestop.toStdString().c_str());
    }

    sort(entriesSortedBegin.begin(), entriesSortedBegin.end(), compareBegin());
    sort(entriesSortedEnd.begin(), entriesSortedEnd.end(), compareEnd());

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
