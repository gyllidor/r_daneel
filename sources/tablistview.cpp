#include "tablistview.h"

#include <QDebug>

TabListView::TabListView(QWidget *parent)
    : QListView(parent)
    , mp_fs_model(new QFileSystemModel())
{
    mp_fs_model->setFilter(QDir::AllEntries | QDir::NoDot);
    setModel(mp_fs_model);
}

TabListView::~TabListView()
{
    delete mp_fs_model;
}

QString TabListView::getRootPath() const
{
    return mp_fs_model->rootPath();
}

void TabListView::onTabClicked(TabButton *ip_tab_button)
{
    qDebug() << __FUNCTION__ << ip_tab_button->getPath();

    changeRootDir(ip_tab_button->getPath());
}

void TabListView::mousePressEvent(QMouseEvent *ip_mouse_event)
{
    if (ip_mouse_event->button() == Qt::MidButton)
        onMidClicked(indexAt(ip_mouse_event->pos()));
    else
        QListView::mousePressEvent(ip_mouse_event);
}

void TabListView::mouseDoubleClickEvent(QMouseEvent *ip_mouse_event)
{
    if (ip_mouse_event->button() == Qt::LeftButton)
        onLeftDoubleClicked(indexAt(ip_mouse_event->pos()));
}

void TabListView::onLeftDoubleClicked(const QModelIndex &i_index)
{
    if (!i_index.isValid())
        return;

    const auto path = mp_fs_model->filePath(i_index);
    if (QFileInfo(path).isDir())
        changeRootDir(path);
}

void TabListView::onMidClicked(const QModelIndex &i_index)
{
    if (!i_index.isValid())
        return;

    const auto path = mp_fs_model->filePath(i_index);
    if (QFileInfo(path).isDir())
        emit midClicked(path);
}

void TabListView::changeRootDir(const QString &i_new_root_dir)
{
    setRootIndex(mp_fs_model->index(i_new_root_dir));
    mp_fs_model->setRootPath(i_new_root_dir);

    emit tabViewRootChanged(this);
}
