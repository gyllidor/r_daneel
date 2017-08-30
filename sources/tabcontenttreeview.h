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

    void setModel(QAbstractItemModel* ip_model) override;

signals:
    void tabRootContentChanged(const QString&);
    void midClicked(const QString&);
    void dirRemoved(const QString&) const;

public slots:
    void onTabClicked(TabButton* ip_tab_button);

protected:
    void mousePressEvent(QMouseEvent* ip_mouse_event) override;
    void mouseDoubleClickEvent(QMouseEvent* ip_mouse_event) override;
    void keyPressEvent(QKeyEvent* ip_event) override;

private:
    void _onLeftDoubleClicked(const QModelIndex& i_index);
    void _onMidClicked(const QModelIndex& i_index);
    void _changeRootDir(const QString& i_new_root_dir);
    void _onPressDelete() const;
    void _onPressReturn();
    void _onPressBackspace();
    void _onPressF7();

private:
    QFileSystemModel* mp_fs_model;
};

} // namesapce qp

#endif // TABCONTENTTREEVIEW_H
