#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui.h"

class MainWindow : public QMainWindow{

    Q_OBJECT

public:
    explicit MainWindow(const QString &dir, QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = 0);
    ~MainWindow();

private:
    DedicatedSlaveUi *dsui_app;

};

#endif
