#include "tabcontenttreeview.h"
#include "tabbutton.h"

#include <QMouseEvent>
#include <QFileSystemModel>
#include <QDesktopServices>

qp::TabContentTreeView::TabContentTreeView(QWidget *parent)
    : QTreeView(parent)
    , mp_fs_model(new QFileSystemModel())
{
    setExpandsOnDoubleClick(false);

    mp_fs_model->setFilter(QDir::Filter::AllEntries | QDir::Filter::NoDot);

    // todo: set from outside
    setModel(mp_fs_model);
    setColumnWidth(0, 300);
}

qp::TabContentTreeView::~TabContentTreeView()
{
    delete mp_fs_model;
}

QString qp::TabContentTreeView::getRootPath() const
{
    return mp_fs_model->rootPath();
}

void qp::TabContentTreeView::onTabClicked(qp::TabButton *ip_tab_button)
{
    changeRootDir(ip_tab_button->getPath());
}

void qp::TabContentTreeView::mousePressEvent(QMouseEvent *ip_mouse_event)
{
    if (Qt::MidButton == ip_mouse_event->button())
        onMidClicked(indexAt(ip_mouse_event->pos()));
    else
        QTreeView::mousePressEvent(ip_mouse_event);
}

void qp::TabContentTreeView::mouseDoubleClickEvent(QMouseEvent *ip_mouse_event)
{
    if (Qt::LeftButton == ip_mouse_event->button())
        onLeftDoubleClicked(indexAt(ip_mouse_event->pos()));
}

void qp::TabContentTreeView::onLeftDoubleClicked(const QModelIndex &i_index)
{
    if (!i_index.isValid())
        return;

    const auto path = mp_fs_model->fileInfo(i_index).absoluteFilePath();
    if (QFileInfo(path).isDir())
        changeRootDir(path);
    else
        QDesktopServices::openUrl(QUrl(QUrl::fromLocalFile(path)));
}

void qp::TabContentTreeView::onMidClicked(const QModelIndex &i_index)
{
    if (!i_index.isValid())
        return;

    const auto path = mp_fs_model->fileInfo(i_index).absoluteFilePath();
    if (QFileInfo(path).isDir())
        emit midClicked(path);
}

void qp::TabContentTreeView::changeRootDir(const QString &i_new_root_dir)
{
    const auto current_index = mp_fs_model->setRootPath(i_new_root_dir);
    setRootIndex(current_index);
    setCurrentIndex(current_index);
    collapseAll();

    emit tabViewRootChanged(i_new_root_dir);
}
