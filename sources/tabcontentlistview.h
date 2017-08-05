#ifndef TABVIEW_H
#define TABVIEW_H

#include <QListView>
#include <QFileSystemModel>

namespace qp
{

class TabButton;

class TabContentListView : public QListView
{
    Q_OBJECT
public:
    explicit TabContentListView(QWidget *parent = 0);
    ~TabContentListView();

    QString getRootPath() const;

signals:
    void tabViewRootChanged(const QString&);
    void midClicked(const QString&);

public slots:
    void onTabClicked(TabButton *ip_tab_button);

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

} // namespace qp

#endif // TABVIEW_H
