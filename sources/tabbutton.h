#ifndef TABBUTTON_H
#define TABBUTTON_H

#include <QPushButton>

class QMouseEvent;

namespace qp
{

class TabButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int m_activated_by READ getActivatedBy WRITE setActivatedBy)

public:
    enum EActivatedBy
    {
        EA_NONE = 0,
        EA_LEFT,
        EA_RIGHT,
        EA_LEFT_RIGHT
    };

public:
    TabButton(const QString& i_dir);
    virtual ~TabButton();

    QString getPath() const;
    void setPath(const QString& i_path);

    void setActivatedBy(int i_activated_by);
    int getActivatedBy() const;

signals:
    void leftClicked(TabButton*);
    void midClicked(TabButton*);
    void rightClicked(TabButton*);

protected:
    void mousePressEvent(QMouseEvent* ip_mouse_event) override;

private:
    QString m_dir;
    int m_activated_by;
};

} // namespace qp

#endif // TABBUTTON_H
