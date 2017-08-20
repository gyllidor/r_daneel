#ifndef CONTROLLERTABS_H
#define CONTROLLERTABS_H

#include <QObject>

class QLayout;

namespace qp
{
class TabButton;

class TabsController : public QObject
{
    Q_OBJECT

public:
    TabsController(QLayout* ip_layout_tabs);
    virtual ~TabsController();

    void Init();

signals:
    void tabClickedLeftBtn(TabButton*);
    void tabClickedRightBtn(TabButton*);

public slots:
    void onViewRootDirChangedLeft(const QString &i_new_root_dir);
    void onViewRootDirChangedRight(const QString& i_new_root_dir);
    void onAddTab(const QString& i_path);
    void onDirRemoved(const QString&);

private slots:
    void onTabLeftClicked(TabButton *ip_tab_button);
    void onTabMidClicked(TabButton *ip_tab_button);
    void onTabRightClicked(TabButton *ip_tab_button);

private:
    void _onViewRootDirChanged(const QString& i_new_root_dir
                              , TabButton*& ip_active_tab_first
                              , TabButton*& ip_active_tab_second);
    TabButton* _findFirstExistanceTab(const QString& i_dir);
    TabButton* _addTab(const QString& i_dir);
    void _updateStyleSheetForActiveTabs();

private:
    QLayout* mp_layout_tabs;
    TabButton* mp_active_tab_left;
    TabButton* mp_active_tab_right;
};

} // namespace qp

#endif // CONTROLLERTABS_H
