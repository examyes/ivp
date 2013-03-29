#include "sidebar.h"

SideBar::SideBar(QWidget *parent) :
    QScrollArea(parent)
{
    setBackgroundRole(QPalette::Dark);

    title = new QLabel("This a title");
    text = new QLabel("This is some text");

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

SideBar::~SideBar(){
    delete title;
    delete text;
}
