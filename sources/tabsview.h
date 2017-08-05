#ifndef CONTROLLERTABS_H
#define CONTROLLERTABS_H

#include "tabcontentlistview.h"

#include <QLayout>

#include <set>
#include <memory>

namespace qp
{
class TabButton;

class TabsView : public QObject
{
    Q_OBJECT

public:
    TabsView(QLayout* ip_layout_tabs);
    virtual ~TabsView();

    void Init();

signals:
    void tabClickedLeftBtn(TabButton*);
    void tabClickedRight(TabButton*);

public slots:
    void onViewRootDirChangedFirst(const TabContentListView* ip_tab_view);
    void onViewRootDirChangedSecond(const TabContentListView* ip_tab_view);
    void onAddTab(const QString& i_path);

private slots:
    void onTabLeftClicked(TabButton *ip_tab_button);
    void onTabMidClicked(TabButton *ip_tab_button);
    void onTabRightClicked(TabButton *ip_tab_button);

private:
    void onViewRootDirChanged(const TabContentListView* ip_tab_view
                              , TabButton*& ip_active_tab_first
                              , TabButton*& ip_active_tab_second);
    TabButton* findFirstExistanceTab(const QString& i_dir);
    TabButton* addTab(const QString& i_dir);

private:
    QLayout* mp_layout_tabs;
    TabButton* mp_active_tab_first;
    TabButton* mp_active_tab_second;
};

} // namespace qp

#endif // CONTROLLERTABS_H
