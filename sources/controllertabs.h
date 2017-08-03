#ifndef CONTROLLERTABS_H
#define CONTROLLERTABS_H

#include "tabbutton.h"
#include "tablistview.h"

#include <QLayout>

#include <set>
#include <memory>

class ControllerTabs : public QObject
{
    Q_OBJECT

public:
    ControllerTabs(QLayout* ip_layout_tabs);
    virtual ~ControllerTabs();

    void Init();

signals:
    void tabClickedLeftBtn(TabButton*);
    void tabClickedRight(TabButton*);

public slots:
    void onViewRootDirChangedFirst(const TabListView* ip_tab_view);
    void onViewRootDirChangedSecond(const TabListView* ip_tab_view);
    void onAddTab(const QString& i_path);

private slots:
    void onTabLeftClicked(TabButton *ip_tab_button);
    void onTabMidClicked(TabButton *ip_tab_button);
    void onTabRightClicked(TabButton *ip_tab_button);

private:
    void onViewRootDirChanged(const TabListView* ip_tab_view
                              , TabButton*& ip_active_tab_first
                              , TabButton*& ip_active_tab_second);
    TabButton* findFirstExistanceTab(const QString& i_dir);
    TabButton* addTab(const QString& i_dir);

private:
    QLayout* mp_layout_tabs;
    TabButton* mp_active_tab_first;
    TabButton* mp_active_tab_second;
};

#endif // CONTROLLERTABS_H
