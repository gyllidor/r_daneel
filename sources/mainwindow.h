#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

namespace qp
{
class TabsController;
class TabContentTreeView;
}

namespace Ui
{
class MainWindow;
}

namespace qp
{
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<qp::TabsController> mp_controller_tabs;
    TabContentTreeView* mp_tab_view_left;
    TabContentTreeView* mp_tab_view_right;
};
} // namespace qp

#endif // MAINWINDOW_H
