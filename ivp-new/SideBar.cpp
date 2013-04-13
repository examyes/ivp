#include "SideBar.h"

SideBar::SideBar(QWidget *parent) :
    QScrollArea(parent)
{
    setBackgroundRole(QPalette::Dark);

    title = new QLabel("");
    text = new QLabel("");

    QVBoxLayout* sidebarLayout = new QVBoxLayout();
    sidebarLayout->addWidget(title);
    sidebarLayout->addWidget(text);

    QWidget* sidebarWidget = new QWidget(this);
    sidebarWidget->setLayout(sidebarLayout);

    setWidget(sidebarWidget);

    setMinimumWidth(300);
    setMaximumWidth(300);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
}

QSize SideBar::sizeHint() const{
    return QSize(300, 500);
}

void SideBar::showItem(MetaItem* item){
    title->setText(item->title);
    text->setText(item->text);
    this->show();
}

SideBar::~SideBar(){
    delete title;
    delete text;
}
