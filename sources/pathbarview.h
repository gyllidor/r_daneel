#ifndef PATHBARVIEW_H
#define PATHBARVIEW_H

#include <QScrollArea>

class QHBoxLayout;
class QWheelEvent;
class QPushButton;

class PathBarView : public QScrollArea
{
    Q_OBJECT

public:
    explicit PathBarView(QWidget *parent = 0);

signals:
    void onDirClicked(const QString& i_dir_path);

public slots:
    void changeRootDir(const QString& i_new_path);

protected:
    void wheelEvent(QWheelEvent* ip_event) override;

private:
    QPushButton *_addButton(const QString& i_text, const QString& i_name);
    void _setButtonMenu(QPushButton* ip_btn, const QString& i_dir_path);
    void _deleteButtons();
    void _addButtons(const QString& i_dir_path);

private:
    QHBoxLayout* mp_layout;
};

#endif // PATHBARVIEW_H
