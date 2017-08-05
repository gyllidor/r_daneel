#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

namespace qp
{
class TabsController;
class TabContentTreeView;
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
    std::unique_ptr<qp::TabsController> mp_controller_tabs;
    qp::TabContentTreeView* mp_tab_view_left;
    qp::TabContentTreeView* mp_tab_view_right;
};

#endif // MAINWINDOW_H
