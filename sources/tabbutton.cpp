#include "tabbutton.h"

#include <QDir>
#include <QDebug>

qp::TabButton::TabButton(const QString &i_dir)
    : QPushButton(nullptr)
{
    setPath(i_dir);
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
    const QString clean_path = QDir().cleanPath(i_path);

    setObjectName(clean_path);
    setText(QFileInfo(clean_path).baseName());
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

