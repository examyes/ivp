#include "SideBar.h"

SideBar::SideBar(QWidget *parent) :
    QScrollArea(parent)
{
    //setBackgroundRole(QPalette::Dark);
    setStyleSheet( "SideBar { border-style: none}" );

    sidebarWidget = new QWidget(this);
    sidebarWidget->setFixedWidth(290);

    title = new QLabel("", sidebarWidget);
    title->setWordWrap(true);

    text = new QLabel("", sidebarWidget);
    text->setWordWrap(true);

    setWidget(sidebarWidget);

    setMinimumWidth(300);
    setMaximumWidth(300);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);

}

QSize SideBar::sizeHint() const{
    return QSize(300, 500);
}

void SideBar::showItem(MetaItem* item){
    title->setText("<big>" + item->title + "</big>");
    title->setGeometry(0, 0, 280, title->heightForWidth(280)+20);
    title->show();

    text->setText(item->text);
    text->setGeometry(0, title->size().height()+10, 280, text->heightForWidth(280)+20);
    text->show();

    sidebarWidget->setFixedHeight(title->size().height() + text->size().height() + 50);

    show();
}

SideBar::~SideBar(){
    delete title;
    delete text;
}
