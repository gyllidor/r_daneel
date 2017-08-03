#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "controllertabs.h"

#include <QGridLayout>
#include <QPushButton>
#include <QListView>
#include <QFileSystemModel>
#include <QScrollArea>
#include <QDebug>

#include "tabbutton.h"
#include "tablistview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->verticalLayout->setAlignment(Qt::AlignTop);

    mp_controller_tabs = std::make_unique<ControllerTabs>(ui->verticalLayout);
    mp_tab_view_left = new TabListView(ui->centralWidget);
    mp_tab_view_right = new TabListView(ui->centralWidget);
    mp_tab_view_left->setObjectName(QStringLiteral("tabLiestViewLeft"));
    mp_tab_view_right->setObjectName(QStringLiteral("tabLiestViewRight"));

    ui->gridLayout->addWidget(mp_tab_view_left, 0, 0, 1, 1);
    ui->gridLayout->addWidget(mp_tab_view_right, 0, 2, 1, 1);

    connect(mp_controller_tabs.get(), &ControllerTabs::tabClickedLeftBtn
            , mp_tab_view_left, &TabListView::onTabClicked);

    connect(mp_controller_tabs.get(), &ControllerTabs::tabClickedRight
            , mp_tab_view_right, &TabListView::onTabClicked);

    connect(mp_tab_view_left, &TabListView::tabViewRootChanged,
            mp_controller_tabs.get(), &ControllerTabs::onViewRootDirChangedFirst);

    connect(mp_tab_view_right, &TabListView::tabViewRootChanged,
            mp_controller_tabs.get(), &ControllerTabs::onViewRootDirChangedSecond);

    connect(mp_tab_view_left, &TabListView::midClicked,
            mp_controller_tabs.get(), &ControllerTabs::onAddTab);

    connect(mp_tab_view_right, &TabListView::midClicked,
            mp_controller_tabs.get(), &ControllerTabs::onAddTab);

    mp_controller_tabs->Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
