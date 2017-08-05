#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QListView>

#include <memory>

namespace qp
{
class TabsView;
class TabContentListView;
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<qp::TabsView> mp_controller_tabs;
    qp::TabContentListView* mp_tab_view_left;
    qp::TabContentListView* mp_tab_view_right;
};

#endif // MAINWINDOW_H
