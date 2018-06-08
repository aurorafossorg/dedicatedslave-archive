#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow(const QString &dir, QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags){

    qInfo() << "(CLASS)\tInitializing 'DedicatedSlaveUi' class...";
    dsui_app = new DedicatedSlaveUi(dir, this);
    qInfo() << "(CLASS)\t'DedicatedSlaveUi'initialized.";
    setMinimumSize(500, 500);
    resize(750, 750);
    setUnifiedTitleAndToolBarOnMac(true);
}

MainWindow::~MainWindow(){

    delete dsui_app;

}
