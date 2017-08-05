#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tabsview.h"

#include <QGridLayout>
#include <QPushButton>
#include <QListView>
#include <QFileSystemModel>
#include <QScrollArea>
#include <QDebug>

#include "tabbutton.h"
#include "tabcontentlistview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->verticalLayout->setAlignment(Qt::AlignTop);

    mp_controller_tabs = std::make_unique<qp::TabsView>(ui->verticalLayout);
    mp_tab_view_left = new qp::TabContentListView(ui->centralWidget);
    mp_tab_view_right = new qp::TabContentListView(ui->centralWidget);
    mp_tab_view_left->setObjectName(QStringLiteral("tabLiestViewLeft"));
    mp_tab_view_right->setObjectName(QStringLiteral("tabLiestViewRight"));

    ui->gridLayout->addWidget(mp_tab_view_left, 0, 0, 1, 1);
    ui->gridLayout->addWidget(mp_tab_view_right, 0, 2, 1, 1);

    connect(mp_controller_tabs.get(), &qp::TabsView::tabClickedLeftBtn
            , mp_tab_view_left, &qp::TabContentListView::onTabClicked);

    connect(mp_controller_tabs.get(), &qp::TabsView::tabClickedRight
            , mp_tab_view_right, &qp::TabContentListView::onTabClicked);

    connect(mp_tab_view_left, &qp::TabContentListView::tabViewRootChanged,
            mp_controller_tabs.get(), &qp::TabsView::onViewRootDirChangedFirst);

    connect(mp_tab_view_right, &qp::TabContentListView::tabViewRootChanged,
            mp_controller_tabs.get(), &qp::TabsView::onViewRootDirChangedSecond);

    connect(mp_tab_view_left, &qp::TabContentListView::midClicked,
            mp_controller_tabs.get(), &qp::TabsView::onAddTab);

    connect(mp_tab_view_right, &qp::TabContentListView::midClicked,
            mp_controller_tabs.get(), &qp::TabsView::onAddTab);

    mp_controller_tabs->Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
