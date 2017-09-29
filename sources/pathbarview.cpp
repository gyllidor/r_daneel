#include "pathbarview.h"

#include <QPushButton>
#include <QDebug>
#include <QWheelEvent>
#include <QScrollBar>
#include <QApplication>
#include <QDir>
#include <QLayout>
#include <QAction>
#include <QMenu>
#include <QStyle>

namespace
{
namespace Const
{
constexpr int max_dir_button_width = 100;
const QString separator = QStringLiteral(">");
}

QStringList _splitIntoDirs(const QString& i_dir)
{
    return QStringList(QDir::rootPath()) + i_dir.split(QDir::separator(), QString::SkipEmptyParts);
}

QString _composeCleanPath(const QString& i_dir, const QString& i_subdir)
{
    return QDir::cleanPath(i_dir + QDir::separator() + i_subdir);
}
} // anonymous namespace

PathBarView::PathBarView(QWidget *parent)
    : QScrollArea(parent)
    , mp_layout(nullptr)
{
    setWidgetResizable(true);

    auto content = new QWidget();
    mp_layout = new QHBoxLayout(content);
    mp_layout->setAlignment(Qt::AlignLeft);

    setWidget(content);
}

void PathBarView::changeRootDir(const QString &i_new_path)
{
    if (!widget()->findChild<QPushButton*>(i_new_path))
    {
        _deleteButtons();
        _addButtons(i_new_path);
    }

    const auto buttons = widget()->findChildren<QPushButton*>();
    for (auto p_button : buttons)
    {
        p_button->setDefault(p_button->objectName() == i_new_path);
        p_button->style()->polish(p_button);
    }
}

void PathBarView::wheelEvent(QWheelEvent *ip_event)
{
    QApplication::sendEvent(horizontalScrollBar(), ip_event);
    ip_event->accept();
}

QPushButton* PathBarView::_addButton(const QString &i_text, const QString &i_name)
{
    auto p_btn = new QPushButton();

    const auto metrics = p_btn->fontMetrics();
    const auto elided_text = metrics.elidedText(i_text, Qt::ElideMiddle, Const::max_dir_button_width);
    const auto elided_width = metrics.width(elided_text) + metrics.xHeight();
    const auto btn_height = height() - contentsMargins().bottom() - contentsMargins().top();

    p_btn->setObjectName(i_name);
    p_btn->setText(elided_text);
    p_btn->setMaximumSize(elided_width, btn_height);
    p_btn->setMinimumSize(elided_width, btn_height);

    mp_layout->addWidget(p_btn);
    return p_btn;
}

void PathBarView::_setButtonMenu(QPushButton *ip_btn, const QString &i_dir_path)
{
    QList<QAction*> actions;
    const auto dirs = QDir(i_dir_path).entryList(QDir::NoDotAndDotDot| QDir::AllDirs);
    for (int i = 0; i < dirs.size(); ++i)
    {
        const QString path = _composeCleanPath(i_dir_path, dirs[i]);

        auto* p_action = new QAction(dirs[i ], ip_btn);
        actions.append(p_action);

        connect(p_action, &QAction::triggered, [this, path](){ onDirClicked(path); });
    }

    if (!actions.empty())
    {
        auto p_menu = new QMenu(ip_btn);
        p_menu->addActions(actions);
        ip_btn->setMenu(p_menu);
        ip_btn->setStyleSheet("QPushButton::menu-indicator{image:\"\"; width:0px;}");
    }
}

void PathBarView::_deleteButtons()
{
    while (auto p_item = mp_layout->takeAt(0))
    {
        delete p_item->widget();
        delete p_item;
    }
}

void PathBarView::_addButtons(const QString &i_dir_path)
{
    QString path;
    const QStringList dirs = _splitIntoDirs(QDir::cleanPath(i_dir_path));
    for (int i = 0; i < dirs.size(); ++i)
    {
        path = _composeCleanPath(path, dirs[i]);

        auto p_btn = _addButton(dirs.at(i), path);
        connect(p_btn, &QPushButton::clicked, [this, path](){ onDirClicked(path); });

        if (i < dirs.size() - 1)
            _setButtonMenu(_addButton(Const::separator, Const::separator), path);
    }
}
