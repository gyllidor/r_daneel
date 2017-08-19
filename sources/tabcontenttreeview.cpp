#include "tabcontenttreeview.h"
#include "tabbutton.h"

#include <QMouseEvent>
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QHeaderView>
#include <QDebug>

qp::TabContentTreeView::TabContentTreeView(QWidget *parent)
    : QTreeView(parent)
    , mp_fs_model(nullptr)
{
    setExpandsOnDoubleClick(false);
}

qp::TabContentTreeView::~TabContentTreeView()
{
}

QString qp::TabContentTreeView::getRootPath() const
{
    return mp_fs_model->rootPath();
}

void qp::TabContentTreeView::setModel(QAbstractItemModel *ip_model)
{
    mp_fs_model = dynamic_cast<QFileSystemModel*>(ip_model);

    QTreeView::setModel(ip_model);

    setColumnWidth(0, 250);
}

void qp::TabContentTreeView::onTabClicked(qp::TabButton *ip_tab_button)
{
    _changeRootDir(ip_tab_button->getPath());
}

void qp::TabContentTreeView::mousePressEvent(QMouseEvent *ip_mouse_event)
{
    if (Qt::MidButton == ip_mouse_event->button())
        _onMidClicked(indexAt(ip_mouse_event->pos()));
    else
        QTreeView::mousePressEvent(ip_mouse_event);
}

void qp::TabContentTreeView::mouseDoubleClickEvent(QMouseEvent *ip_mouse_event)
{
    if (Qt::LeftButton == ip_mouse_event->button())
        _onLeftDoubleClicked(indexAt(ip_mouse_event->pos()));
}

void qp::TabContentTreeView::keyPressEvent(QKeyEvent *ip_event)
{
    switch (ip_event->key())
    {
    case Qt::Key_Delete:
    {
        if (ip_event->modifiers() == Qt::KeyboardModifier::ShiftModifier)
            _onPressDelete();
        break;
    }

    case Qt::Key_F5:
        qDebug() << "Key_F5";
        break;

    case Qt::Key_F6:
        qDebug() << "Key_F6";
        break;

    case Qt::Key_Return:
    {
        if (state() != State::EditingState)
            _onPressReturn();
        break;
    }

    case Qt::Key_Backspace:
    {
        _onPressBackspace();
        break;
    }

    case Qt::Key_F7:
    {
        _onPressF7();
        break;
    }

    default:
        QTreeView::keyPressEvent(ip_event);

    } // switch
}

void qp::TabContentTreeView::_onLeftDoubleClicked(const QModelIndex &i_index)
{
    if (!i_index.isValid())
        return;

    const auto path = mp_fs_model->fileInfo(i_index).absoluteFilePath();
    if (QFileInfo(path).isDir())
        _changeRootDir(path);
    else
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

void qp::TabContentTreeView::_onMidClicked(const QModelIndex &i_index)
{
    if (!i_index.isValid())
        return;

    const auto path = mp_fs_model->fileInfo(i_index).absoluteFilePath();
    if (QFileInfo(path).isDir())
        emit midClicked(path);
}

void qp::TabContentTreeView::_changeRootDir(const QString &i_new_root_dir)
{
    const auto current_index = mp_fs_model->setRootPath(i_new_root_dir);
    setRootIndex(current_index);
    setCurrentIndex(current_index);
    collapseAll();

    emit tabViewRootChanged(i_new_root_dir);
}

void qp::TabContentTreeView::_onPressDelete() const
{
    const auto indexes = selectedIndexes();
    QSet<QString> files;
    for (const auto& index : indexes)
        files.insert(mp_fs_model->filePath(index));

    for (const auto& file : files)
    {
        if (QFileInfo(file).isDir())
        {
            QDir dir(file);
            dir.removeRecursively();
            dirRemoved(file);
        }
        else
        {
            QFile file_path(file);
            file_path.remove();
        }
    }
}

void qp::TabContentTreeView::_onPressReturn()
{
    const auto indexes = selectedIndexes();
    int count_visible_col = header()->count();
    for (int i = 0; i < header()->count(); ++i)
        if (header()->isSectionHidden(i))
            --count_visible_col;

    if (indexes.size() == count_visible_col)
        _onLeftDoubleClicked(indexes.at(0));
}

void qp::TabContentTreeView::_onPressBackspace()
{
    QDir current_dir(getRootPath());
    if (current_dir.cdUp())
        _changeRootDir(current_dir.cleanPath(current_dir.path()));
}

void qp::TabContentTreeView::_onPressF7()
{
    const QFileInfo file_info(getRootPath());
    if (!file_info.isWritable())
        return;

    QDir temp_dir(getRootPath());
    size_t i = 0;
    do
    {
        QString new_dir = getRootPath().append(QDir::separator());
        new_dir.append("new_folder_");
        new_dir.append(QString::number(i++));

        temp_dir = new_dir;
    }
    while(!temp_dir.mkdir(temp_dir.path()));
}
