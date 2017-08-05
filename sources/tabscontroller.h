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
    void tabClickedRight(TabButton*);

public slots:
    void onViewRootDirChangedFirst(const QString &i_new_root_dir);
    void onViewRootDirChangedSecond(const QString& i_new_root_dir);
    void onAddTab(const QString& i_path);

private slots:
    void onTabLeftClicked(TabButton *ip_tab_button);
    void onTabMidClicked(TabButton *ip_tab_button);
    void onTabRightClicked(TabButton *ip_tab_button);

private:
    void onViewRootDirChanged(const QString& i_new_root_dir
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
