#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tabscontroller.h"
#include "tabbutton.h"
#include "tabcontenttreeview.h"

#include <QGridLayout>
#include <QPushButton>
#include <QListView>
#include <QFileSystemModel>
#include <QScrollArea>
#include <QDebug>

qp::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->verticalLayout->setAlignment(Qt::AlignTop);

    mp_controller_tabs = std::make_unique<TabsController>(ui->verticalLayout);
    mp_tab_view_left = new TabContentTreeView(ui->centralWidget);
    mp_tab_view_right = new TabContentTreeView(ui->centralWidget);
    mp_tab_view_left->setObjectName(QStringLiteral("tabLiestViewLeft"));
    mp_tab_view_right->setObjectName(QStringLiteral("tabLiestViewRight"));

    ui->gridLayout->addWidget(mp_tab_view_left, 0, 0, 1, 1);
    ui->gridLayout->addWidget(mp_tab_view_right, 0, 2, 1, 1);

    connect(mp_controller_tabs.get(), &TabsController::tabClickedLeftBtn
            , mp_tab_view_left, &TabContentTreeView::onTabClicked);

    connect(mp_controller_tabs.get(), &TabsController::tabClickedRight
            , mp_tab_view_right, &TabContentTreeView::onTabClicked);

    connect(mp_tab_view_left, &TabContentTreeView::tabViewRootChanged,
            mp_controller_tabs.get(), &TabsController::onViewRootDirChangedFirst);

    connect(mp_tab_view_right, &TabContentTreeView::tabViewRootChanged,
            mp_controller_tabs.get(), &TabsController::onViewRootDirChangedSecond);

    connect(mp_tab_view_left, &TabContentTreeView::midClicked,
            mp_controller_tabs.get(), &TabsController::onAddTab);

    connect(mp_tab_view_right, &TabContentTreeView::midClicked,
            mp_controller_tabs.get(), &TabsController::onAddTab);

    mp_controller_tabs->Init();
}

qp::MainWindow::~MainWindow()
{
    delete ui;
}
