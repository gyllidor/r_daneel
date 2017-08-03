#ifndef TABVIEW_H
#define TABVIEW_H

#include "tabbutton.h"

#include <QListView>
#include <QFileSystemModel>

class TabListView : public QListView
{
    Q_OBJECT
public:
    explicit TabListView(QWidget *parent = 0);
    ~TabListView();

    QString getRootPath() const;

signals:
    void tabViewRootChanged(const TabListView*);
    void midClicked(const QString&);

public slots:
    void onTabClicked(TabButton *ip_tab_button);

protected:
    void mousePressEvent(QMouseEvent* ip_mouse_event);
    void mouseDoubleClickEvent(QMouseEvent* ip_mouse_event) override;

private:
    void onLeftDoubleClicked(const QModelIndex& i_index);
    void onMidClicked(const QModelIndex& i_index);
    void changeRootDir(const QString& i_new_root_dir);

private:
    QFileSystemModel* mp_fs_model;
};

#endif // TABVIEW_H
