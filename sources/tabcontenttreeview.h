#ifndef TABCONTENTTREEVIEW_H
#define TABCONTENTTREEVIEW_H

#include <QTreeView>

class QFileSystemModel;

namespace qp
{
class TabButton;

class TabContentTreeView : public QTreeView
{
    Q_OBJECT
public:
    TabContentTreeView(QWidget* parent = 0);
    ~TabContentTreeView();

    QString getRootPath() const;

signals:
    void tabViewRootChanged(const QString&);
    void midClicked(const QString&);

public slots:
    void onTabClicked(TabButton* ip_tab_button);

protected:
    void mousePressEvent(QMouseEvent* ip_mouse_event) override;
    void mouseDoubleClickEvent(QMouseEvent* ip_mouse_event) override;

private:
    void onLeftDoubleClicked(const QModelIndex& i_index);
    void onMidClicked(const QModelIndex& i_index);
    void changeRootDir(const QString& i_new_root_dir);

private:
    QFileSystemModel* mp_fs_model;
};

} // namesapce qp

#endif // TABCONTENTTREEVIEW_H
