#include "tabbutton.h"

#include <QMouseEvent>
#include <QDir>

#include <QDebug>

qp::TabButton::TabButton(const QString &i_dir)
    : QPushButton(nullptr)
{
    setPath(i_dir);
    setFocusPolicy(Qt::FocusPolicy::NoFocus);
}

qp::TabButton::~TabButton()
{
}

QString qp::TabButton::getPath() const
{
    return objectName();
}

void qp::TabButton::setPath(const QString &i_path)
{
    setObjectName(i_path);
    setText(QDir::rootPath() != i_path ? QFileInfo(i_path).baseName() : QDir::rootPath());
}

void qp::TabButton::mousePressEvent(QMouseEvent *ip_mouse_event)
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

