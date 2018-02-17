#ifndef UIDOCK_H
#define UIDOCK_H

#include <QDockWidget>
#include <QFormLayout>
#include <QGroupBox>
#include <QTabWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <QLabel>
#include <QLineEdit>

class UiDockOptions : public QDockWidget{
	Q_OBJECT

public:
	UiDockOptions(const QString &title, QWidget *parent = 0);
	void updateModelInst(QString nameId, QString serverName, int numPlayers);

public slots:

private:
	QLineEdit *instName;
	QLineEdit *lineServerName;
	QLineEdit *lineNumPlayers;
	QTabWidget *ui_dockInstOpt;
	QFormLayout *dockInstOptTab1Layout;
	QGroupBox *dockInstOptTab1;
	QGroupBox *dockInstOptTab2;

};

class UiDockFileSystem : public QDockWidget{
	Q_OBJECT

public:
	UiDockFileSystem(const QString &test, QWidget *parent = 0);

public slots:

private:
	QFileSystemModel *app_dirModel;
	QTreeView *ui_dockTreeView;

};

#endif // UIDOCK_H
