#include <QtWidgets>

#include "uidock.h"

UiDockFileSystem::UiDockFileSystem(const QString &title, QWidget *parent) : QDockWidget(title, parent){

    ui_dockTreeView = new QTreeView(parent);

    app_dirModel = new QFileSystemModel;
    app_dirModel->setRootPath("/");
    //    ds_dirModel->setRootPath("");
//    ds_dirModel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    app_dirModel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);
    //        QStringList dirModelFilters;
    //        dirModelFilters << "*.txt" << "*.sh";
    //        app_dirModel->setNameFilters(dirModelFilters);
    //        app_dirModel->setNameFilterDisables(false);
    ui_dockTreeView->setModel(app_dirModel);
    ui_dockTreeView->setRootIndex(app_dirModel->index(QDir::currentPath()));

    this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    this->setWidget(ui_dockTreeView);

}

UiDockOptions::UiDockOptions(const QString &title, QWidget *parent) : QDockWidget(title, parent){

    ui_dockInstOpt = new QTabWidget(parent);

    // Tab 1
    QGroupBox *dockInstOptTab1 = new QGroupBox(this);
    QFormLayout *dockInstOptTab1Layout = new QFormLayout;
    //    QVBoxLayout *vbox = new QVBoxLayout;
    QLabel *labelInstName = new QLabel(dockInstOptTab1);
    QLabel *labelNumPlayers = new QLabel(dockInstOptTab1);
    QLabel *labelServerName = new QLabel(dockInstOptTab1);
    instName = new QLineEdit(dockInstOptTab1);
    QPushButton *okButton = new QPushButton(dockInstOptTab1);
    QPushButton *advButton = new QPushButton(dockInstOptTab1);
    lineNumPlayers = new QLineEdit(dockInstOptTab1);
    lineServerName = new QLineEdit(dockInstOptTab1);
    QRadioButton *radio = new QRadioButton(tr("..."));
    okButton->setText(tr("Save"));
    advButton->setText(tr("Advanced Options"));
    labelInstName->setText(tr("Instance Name"));
    labelNumPlayers->setText(tr("Num Players"));
    labelServerName->setText(tr("Server Name"));
    instName->setDisabled(true);
    dockInstOptTab1Layout->addRow(labelInstName, instName);
    dockInstOptTab1Layout->addRow(labelNumPlayers, lineNumPlayers);
    dockInstOptTab1Layout->addRow(labelServerName, lineServerName);
    dockInstOptTab1Layout->addWidget(advButton);
    dockInstOptTab1Layout->addWidget(okButton);
    dockInstOptTab1->setLayout(dockInstOptTab1Layout);
    //Tab 2
    QGroupBox *dockInstOptTab2 = new QGroupBox;
    QFormLayout *dockInstOptTab2Layout = new QFormLayout;
    QPushButton *svCheatsOn = new QPushButton(dockInstOptTab2);
    QPushButton *svCheatsOff = new QPushButton(dockInstOptTab2);
    svCheatsOn->setText(tr("Cheats ON"));
    svCheatsOff->setText(tr("Cheats OFF"));
    dockInstOptTab2Layout->addRow(svCheatsOn, svCheatsOff);
    dockInstOptTab2->setLayout(dockInstOptTab2Layout);

    ui_dockInstOpt->addTab(dockInstOptTab1, tr("Settings"));
    ui_dockInstOpt->addTab(dockInstOptTab2, tr("Templates"));
    this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    this->setWidget(ui_dockInstOpt);

}

void UiDockOptions::updateModelInst(QString nameId, QString serverName, int numPlayers){
    instName->setText(nameId);
    lineServerName->setText(serverName);
    lineNumPlayers->setText(QString::number(numPlayers));
}
