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

    hideButton = new QPushButton(tr("Hide Sidebar"), this);
    connect(hideButton, SIGNAL(clicked()), this, SLOT(hide()));

    setWidget(sidebarWidget);

    setMinimumWidth(300);
    setMaximumWidth(300);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);

}

QSize SideBar::sizeHint() const{
    return QSize(300, 500);
}

void SideBar::showItem(MetaItem* item){
    hideButton->move(180,0);

    title->setText("<big>" + item->title + "</big>");
    title->setGeometry(0, 40, 280, title->heightForWidth(280)+20);
    title->show();

    text->setText(item->text);
    text->setGeometry(0, title->size().height()+50, 280, text->heightForWidth(280)+20);
    text->show();

    sidebarWidget->setFixedHeight(title->size().height() + text->size().height() + 90);

    show();
}

SideBar::~SideBar(){
    delete title;
    delete text;
}
