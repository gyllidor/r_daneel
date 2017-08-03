#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QListView>

#include <memory>

class ControllerTabs;
class TabListView;

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
    std::unique_ptr<ControllerTabs> mp_controller_tabs;
    TabListView* mp_tab_view_left;
    TabListView* mp_tab_view_right;
};

#endif // MAINWINDOW_H
