#include "tabscontroller.h"
#include "tabbutton.h"

#include <QMouseEvent>
#include <QLayout>
#include <QDir>

qp::TabsController::TabsController(QLayout *ip_layout_tabs)
    : QObject()
    , mp_layout_tabs(ip_layout_tabs)
    , mp_active_tab_first(nullptr)
    , mp_active_tab_second(nullptr)
{
}

qp::TabsController::~TabsController()
{
}

void qp::TabsController::Init()
{
    auto p_tab_button = addTab(QDir::homePath());
    onTabLeftClicked(p_tab_button);
    onTabRightClicked(p_tab_button);
}

void qp::TabsController::onViewRootDirChangedFirst(const QString& i_new_root_dir)
{
    onViewRootDirChanged(i_new_root_dir, mp_active_tab_first, mp_active_tab_second);
}

void qp::TabsController::onViewRootDirChangedSecond(const QString& i_new_root_dir)
{
    onViewRootDirChanged(i_new_root_dir, mp_active_tab_second, mp_active_tab_first);
}

void qp::TabsController::onAddTab(const QString &i_path)
{
    addTab(i_path);
}

void qp::TabsController::onTabLeftClicked(TabButton *ip_tab_button)
{
    mp_active_tab_first = ip_tab_button;
    emit tabClickedLeftBtn(mp_active_tab_first);
}

void qp::TabsController::onTabMidClicked(TabButton *ip_tab_button)
{
    mp_layout_tabs->removeWidget(ip_tab_button);
    ip_tab_button->deleteLater();
    if (mp_layout_tabs->isEmpty())
    {
        auto p_tab_button = addTab(QDir::homePath());
        onTabLeftClicked(p_tab_button);
        onTabRightClicked(p_tab_button);
    }
}

void qp::TabsController::onTabRightClicked(TabButton *ip_tab_button)
{
    mp_active_tab_second = ip_tab_button;
    emit tabClickedRight(mp_active_tab_second);
}

void qp::TabsController::onViewRootDirChanged(const QString& i_new_root_dir
                                          , TabButton *& ip_active_tab_first
                                          , TabButton *& ip_active_tab_second)
{
    if (TabButton* p_tab = findFirstExistanceTab(i_new_root_dir))
    {
        ip_active_tab_first = p_tab;
        return;
    }

    const bool tabs_initialised = ip_active_tab_first && ip_active_tab_second;
    if (tabs_initialised && ip_active_tab_first == ip_active_tab_second
            && ip_active_tab_first->getPath() != i_new_root_dir)
        ip_active_tab_first = addTab(i_new_root_dir);
    else
        ip_active_tab_first->setPath(i_new_root_dir);
}

qp::TabButton *qp::TabsController::findFirstExistanceTab(const QString &i_dir)
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

qp::TabButton *qp::TabsController::addTab(const QString &i_dir)
{
    auto p_tab_button = new TabButton(i_dir);
    connect(p_tab_button, SIGNAL(leftClicked(TabButton*)),
            this, SLOT(onTabLeftClicked(TabButton*)));

    connect(p_tab_button, SIGNAL(midClicked(TabButton*)),
            this, SLOT(onTabMidClicked(TabButton*)));

    connect(p_tab_button, SIGNAL(rightClicked(TabButton*)),
            this, SLOT(onTabRightClicked(TabButton*)));

    mp_layout_tabs->addWidget(p_tab_button);

    return p_tab_button;
}
