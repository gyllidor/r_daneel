#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tabscontroller.h"
#include "tabbutton.h"
#include "tabcontenttreeview.h"

#include <QDir>
#include <QFileSystemModel>

namespace
{
void setupAndSetFileSystemModelFor(QAbstractItemView* ip_view)
{
    auto fs_model_left = new QFileSystemModel(ip_view);
    fs_model_left->setFilter(QDir::Filter::AllEntries | QDir::Filter::NoDot);
    fs_model_left->setReadOnly(false);

    ip_view->setModel(fs_model_left);
}
} // anonymous namespace

qp::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->verticalLayout->setAlignment(Qt::AlignTop);

    auto p_controller_tabs = new TabsController(ui->verticalLayout);
    auto p_tab_view_left = new TabContentTreeView(ui->centralWidget);
    auto p_tab_view_right = new TabContentTreeView(ui->centralWidget);
    p_tab_view_left->setObjectName(QStringLiteral("tabTreeViewLeft"));
    p_tab_view_right->setObjectName(QStringLiteral("tabTreeViewRight"));

    setupAndSetFileSystemModelFor(p_tab_view_left);
    setupAndSetFileSystemModelFor(p_tab_view_right);

    ui->gridLayout->addWidget(p_tab_view_left, 0, 0, 1, 1);
    ui->gridLayout->addWidget(p_tab_view_right, 0, 2, 1, 1);

    connect(p_controller_tabs, &TabsController::tabClickedLeftBtn
            , p_tab_view_left, &TabContentTreeView::onTabClicked);

    connect(p_controller_tabs, &TabsController::tabClickedRightBtn
            , p_tab_view_right, &TabContentTreeView::onTabClicked);

    connect(p_tab_view_left, &TabContentTreeView::tabViewRootChanged,
            p_controller_tabs, &TabsController::onViewRootDirChangedLeft);

    connect(p_tab_view_right, &TabContentTreeView::tabViewRootChanged,
            p_controller_tabs, &TabsController::onViewRootDirChangedRight);

    connect(p_tab_view_left, &TabContentTreeView::midClicked,
            p_controller_tabs, &TabsController::onAddTab);

    connect(p_tab_view_right, &TabContentTreeView::midClicked,
            p_controller_tabs, &TabsController::onAddTab);

    connect(p_tab_view_left, &TabContentTreeView::dirRemoved,
            p_controller_tabs, &TabsController::onDirRemoved);

    connect(p_tab_view_right, &TabContentTreeView::dirRemoved,
            p_controller_tabs, &TabsController::onDirRemoved);

    p_controller_tabs->Init();
}

qp::MainWindow::~MainWindow()
{
    delete ui;
}
