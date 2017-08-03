#include "tabbutton.h"

#include <QDir>
#include <QDebug>

TabButton::TabButton(const QString &i_dir)
    : QPushButton(nullptr)
{
    setPath(i_dir);
}

TabButton::~TabButton()
{
}

QString TabButton::getPath() const
{
    return objectName();
}

void TabButton::setPath(const QString &i_path)
{
    setObjectName(i_path);
    setText(QFileInfo(i_path).baseName());
}

void TabButton::mousePressEvent(QMouseEvent *ip_mouse_event)
{
    switch (ip_mouse_event->button())
    {
    case Qt::LeftButton:
        emit leftClicked(this);
        return;

    case Qt::MidButton:
        emit midClicked(this);
        return;

    case Qt::RightButton:
        emit rightClicked(this);
        return;

    default:
        break;
    }

    QPushButton::mousePressEvent(ip_mouse_event);
}

