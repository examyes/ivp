#include "SideBar.h"
#include <QIODevice>

SideBar::SideBar(QWidget *parent) :
    QScrollArea(parent)
{
    //setBackgroundRole(QPalette::Dark);
    setStyleSheet( "SideBar { border-style: none}" );

    sidebarWidget = new QWidget(this);
    sidebarWidget->setFixedWidth(290);

    title = new QLabel("", sidebarWidget);
    title->setWordWrap(true);

    image = new QLabel(sidebarWidget);

    text = new QLabel("", sidebarWidget);
    text->setWordWrap(true);

    hideButton = new QPushButton(tr("Hide Sidebar"), this);
    connect(hideButton, SIGNAL(clicked()), this, SLOT(hide()));

    setWidget(sidebarWidget);

    setMinimumWidth(300);
    setMaximumWidth(300);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);

    connect(&webCtrl, SIGNAL(finished(QNetworkReply*)),
                SLOT(imageLoaded(QNetworkReply*)));
}

QSize SideBar::sizeHint() const{
    return QSize(300, 500);
}

void SideBar::showItem(MetaItem* item){
    hideButton->move(180,0);

    title->setText("<big>" + item->title + "</big>");
    title->setGeometry(0, 40, 280, title->heightForWidth(280)+20);
    title->show();

    if (!item->imgURL.isEmpty()){
        printf("img url: %s\n", item->imgURL.toStdString().c_str());
        loadImage(item->imgURL);
    }
    image->hide();

    text->setText(item->text);
    text->setGeometry(0, title->size().height()+50, 280, text->heightForWidth(280)+20);
    text->show();

    sidebarWidget->setFixedHeight(title->size().height() + text->size().height() + 90);

    show();
}

void SideBar::loadImage(QString urlStr){

    QNetworkRequest request(urlStr);
    webCtrl.get(request);

}

void SideBar::imageLoaded(QNetworkReply* reply){
    if (reply->error() == QNetworkReply::NoError){
        QByteArray data = reply->readAll();

        QPixmap img;
        img.loadFromData(data);
        QPixmap imgScaled = img.scaled(QSize(200, 200), Qt::KeepAspectRatio);
        image->setPixmap(imgScaled);

        QSize imgSize = imgScaled.size();
        image->setGeometry(0, title->size().height()+50, imgSize.width(), imgSize.height());

        text->move(text->pos().x(), text->pos().y() + imgSize.height() + 20);
        sidebarWidget->setFixedHeight(sidebarWidget->size().height() + imgSize.height() + 20);

        image->show();
    }else{
        printf("Error downloading image: %s\n", reply->errorString().toStdString().c_str());
    }
}

SideBar::~SideBar(){
    delete title;
    delete text;
}
