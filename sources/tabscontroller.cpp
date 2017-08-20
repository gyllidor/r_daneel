#include "tabscontroller.h"
#include "tabbutton.h"

#include <QMouseEvent>
#include <QLayout>
#include <QDir>
#include <QStyle>

qp::TabsController::TabsController(QLayout *ip_layout_tabs)
    : QObject(ip_layout_tabs)
    , mp_layout_tabs(ip_layout_tabs)
    , mp_active_tab_left(nullptr)
    , mp_active_tab_right(nullptr)
{
}

qp::TabsController::~TabsController()
{
}

void qp::TabsController::Init()
{
    auto p_tab_button = _addTab(QDir::homePath());
    onTabLeftClicked(p_tab_button);
    onTabRightClicked(p_tab_button);
}

void qp::TabsController::onViewRootDirChangedLeft(const QString& i_new_root_dir)
{
    _onViewRootDirChanged(i_new_root_dir, mp_active_tab_left, mp_active_tab_right);
}

void qp::TabsController::onViewRootDirChangedRight(const QString& i_new_root_dir)
{
    _onViewRootDirChanged(i_new_root_dir, mp_active_tab_right, mp_active_tab_left);
}

void qp::TabsController::onAddTab(const QString &i_path)
{
    _addTab(i_path);
}

void qp::TabsController::onDirRemoved(const QString &)
{
    const auto parent_widget = mp_layout_tabs->parentWidget();
    for (const auto p_tab_button : parent_widget->findChildren<TabButton*>(QString(), Qt::FindDirectChildrenOnly))
        if (!QDir(p_tab_button->getPath()).exists())
            onTabMidClicked(p_tab_button);
}

void qp::TabsController::onTabLeftClicked(TabButton *ip_tab_button)
{
    mp_active_tab_left = ip_tab_button;
    emit tabClickedLeftBtn(mp_active_tab_left);
}

void qp::TabsController::onTabMidClicked(TabButton *ip_tab_button)
{
    mp_layout_tabs->removeWidget(ip_tab_button);
    ip_tab_button->deleteLater();

    if (ip_tab_button == mp_active_tab_left)
        mp_active_tab_left = mp_active_tab_right;

    if (ip_tab_button == mp_active_tab_right)
        mp_active_tab_right = mp_active_tab_left;

    if (mp_layout_tabs->isEmpty())
    {
        auto p_tab_button = _addTab(QDir::homePath());
        onTabLeftClicked(p_tab_button);
        onTabRightClicked(p_tab_button);
    }
}

void qp::TabsController::onTabRightClicked(TabButton *ip_tab_button)
{
    mp_active_tab_right = ip_tab_button;
    emit tabClickedRightBtn(mp_active_tab_right);
}

void qp::TabsController::_onViewRootDirChanged(const QString& i_new_root_dir
                                               , TabButton *& ip_active_tab_first
                                               , TabButton *& ip_active_tab_second)
{
    if (TabButton* p_tab = _findFirstExistanceTab(i_new_root_dir))
    {
        if (ip_active_tab_first->getPath() != i_new_root_dir)
            ip_active_tab_first = p_tab;
    }
    else if (ip_active_tab_first == ip_active_tab_second)
    {
        ip_active_tab_first = _addTab(i_new_root_dir);
    }
    else
    {
        ip_active_tab_first->setPath(i_new_root_dir);
    }

    _updateStyleSheetForActiveTabs();
}

qp::TabButton *qp::TabsController::_findFirstExistanceTab(const QString &i_dir)
{
    const auto parent = mp_layout_tabs->parent();
    return parent->findChild<TabButton*>(i_dir, Qt::FindDirectChildrenOnly);
}

qp::TabButton *qp::TabsController::_addTab(const QString &i_dir)
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

void qp::TabsController::_updateStyleSheetForActiveTabs()
{
    const auto parent = mp_layout_tabs->parent();
    for (auto p_tab_button : parent->findChildren<TabButton*>(QString(), Qt::FindDirectChildrenOnly))
        p_tab_button->setStyleSheet("");

    // create custom states for TabButton
    if (mp_active_tab_left == mp_active_tab_right)
    {
        mp_active_tab_left->setStyleSheet("background-color: #ff7700;");
        mp_active_tab_right->setStyleSheet("background-color: #ff7700;");
        return;
    }

    if (mp_active_tab_left)
        mp_active_tab_left->setStyleSheet("background-color: #00b24d;");

    if (mp_active_tab_right)
        mp_active_tab_right->setStyleSheet("background-color: #0070bb;");
}
