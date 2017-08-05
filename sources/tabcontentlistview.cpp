#include "tabcontentlistview.h"
#include "tabbutton.h"

#include <QDebug>

qp::TabContentListView::TabContentListView(QWidget *parent)
    : QListView(parent)
    , mp_fs_model(new QFileSystemModel())
{
    mp_fs_model->setFilter(QDir::AllEntries | QDir::NoDot);
    setModel(mp_fs_model);
}

qp::TabContentListView::~TabContentListView()
{
    delete mp_fs_model;
}

QString qp::TabContentListView::getRootPath() const
{
    return mp_fs_model->rootPath();
}

void qp::TabContentListView::onTabClicked(TabButton *ip_tab_button)
{
    qDebug() << __FUNCTION__ << ip_tab_button->getPath();

    changeRootDir(ip_tab_button->getPath());
}

void qp::TabContentListView::mousePressEvent(QMouseEvent *ip_mouse_event)
{
    if (ip_mouse_event->button() == Qt::MidButton)
        onMidClicked(indexAt(ip_mouse_event->pos()));
    else
        QListView::mousePressEvent(ip_mouse_event);
}

void qp::TabContentListView::mouseDoubleClickEvent(QMouseEvent *ip_mouse_event)
{
    if (ip_mouse_event->button() == Qt::LeftButton)
        onLeftDoubleClicked(indexAt(ip_mouse_event->pos()));
}

void qp::TabContentListView::onLeftDoubleClicked(const QModelIndex &i_index)
{
    if (!i_index.isValid())
        return;

    const auto path = mp_fs_model->filePath(i_index);
    if (QFileInfo(path).isDir())
        changeRootDir(path);
}

void qp::TabContentListView::onMidClicked(const QModelIndex &i_index)
{
    if (!i_index.isValid())
        return;

    const auto path = mp_fs_model->filePath(i_index);
    if (QFileInfo(path).isDir())
        emit midClicked(path);
}

void qp::TabContentListView::changeRootDir(const QString &i_new_root_dir)
{
    setRootIndex(mp_fs_model->index(i_new_root_dir));
    mp_fs_model->setRootPath(i_new_root_dir);

    emit tabViewRootChanged(this);
}
