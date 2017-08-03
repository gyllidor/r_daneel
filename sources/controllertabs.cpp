#include "controllertabs.h"

#include <QDir>
#include <QDebug>

ControllerTabs::ControllerTabs(QLayout *ip_layout_tabs)
    : QObject()
    , mp_layout_tabs(ip_layout_tabs)
    , mp_active_tab_first(nullptr)
    , mp_active_tab_second(nullptr)
{
}

ControllerTabs::~ControllerTabs()
{
}

void ControllerTabs::Init()
{
    auto p_tab_button = addTab(QDir::homePath());
    onTabLeftClicked(p_tab_button);
    onTabRightClicked(p_tab_button);
}

void ControllerTabs::onViewRootDirChangedFirst(const TabListView *ip_tab_view)
{
    onViewRootDirChanged(ip_tab_view, mp_active_tab_first, mp_active_tab_second);
}

void ControllerTabs::onViewRootDirChangedSecond(const TabListView *ip_tab_view)
{
    onViewRootDirChanged(ip_tab_view, mp_active_tab_second, mp_active_tab_first);
}

void ControllerTabs::onAddTab(const QString &i_path)
{
    addTab(i_path);
}

void ControllerTabs::onTabLeftClicked(TabButton *ip_tab_button)
{
    qDebug() << __FUNCTION__ << ip_tab_button->getPath();

    mp_active_tab_first = ip_tab_button;
    emit tabClickedLeftBtn(mp_active_tab_first);
}

void ControllerTabs::onTabMidClicked(TabButton *ip_tab_button)
{
    mp_layout_tabs->removeWidget(ip_tab_button);
    ip_tab_button->deleteLater();
    if (mp_layout_tabs->isEmpty())
    {
        auto p_tab_button = addTab(QDir::homePath());
        onTabLeftClicked(p_tab_button);
        onTabRightClicked(p_tab_button);
    }

    qDebug() << __FUNCTION__;
}

void ControllerTabs::onTabRightClicked(TabButton *ip_tab_button)
{
    qDebug() << __FUNCTION__ << ip_tab_button->getPath();

    mp_active_tab_second = ip_tab_button;
    emit tabClickedRight(mp_active_tab_second);
}

void ControllerTabs::onViewRootDirChanged(const TabListView *ip_tab_view
                                          , TabButton *& ip_active_tab_first
                                          , TabButton *& ip_active_tab_second)
{
    if (TabButton* p_tab = findFirstExistanceTab(ip_tab_view->getRootPath()))
    {
        ip_active_tab_first = p_tab;
        return;
    }

    const bool tabs_initialised = ip_active_tab_first && ip_active_tab_second;
    if (tabs_initialised && ip_active_tab_first == ip_active_tab_second
            && ip_active_tab_first->getPath() != ip_tab_view->getRootPath())
        ip_active_tab_first = addTab(ip_tab_view->getRootPath());
    else
        ip_active_tab_first->setPath(ip_tab_view->getRootPath());
}

TabButton *ControllerTabs::findFirstExistanceTab(const QString &i_dir)
{
    for (int i = 0; i < mp_layout_tabs->count(); ++i)
    {
        auto p_item = mp_layout_tabs->itemAt(i);
        auto p_widget = dynamic_cast<TabButton*>(p_item->widget());
        if (p_widget->getPath() == i_dir)
            return p_widget;
    }

    return nullptr;
}

TabButton *ControllerTabs::addTab(const QString &i_dir)
{
    auto p_tab_button = new TabButton(i_dir);
    connect(p_tab_button, SIGNAL(leftClicked(TabButton*)),
            this, SLOT(onTabLeftClicked(TabButton*)));

    connect(p_tab_button, SIGNAL(midClicked(TabButton*)),
            this, SLOT(onTabMidClicked(TabButton*)));

    connect(p_tab_button, SIGNAL(rightClicked(TabButton*)),
            this, SLOT(onTabRightClicked(TabButton*)));

    mp_layout_tabs->addWidget(p_tab_button);
    qDebug() << mp_layout_tabs->count();

    return p_tab_button;
}
