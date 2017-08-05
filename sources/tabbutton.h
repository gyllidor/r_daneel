#ifndef TABBUTTON_H
#define TABBUTTON_H

#include <QPushButton>

class QMouseEvent;

namespace qp
{

class TabButton : public QPushButton
{
    Q_OBJECT

public:
    TabButton(const QString& i_dir);
    virtual ~TabButton();

    QString getPath() const;
    void setPath(const QString& i_path);

signals:
    void leftClicked(TabButton*);
    void midClicked(TabButton*);
    void rightClicked(TabButton*);

protected:
    void mousePressEvent(QMouseEvent* ip_mouse_event) override;

private:
    QString m_dir;
};

} // namespace qp

#endif // TABBUTTON_H
