#ifndef DEDICATEDSLAVE_UI_CONFIGDIALOG_H
#define DEDICATEDSLAVE_UI_CONFIGDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedWidget>

#include <DedicatedSlave/logic/app.h>

class ConfigDialog : public QDialog {
	Q_OBJECT
public:
	ConfigDialog(DedicatedSlaveApp *app);

public slots:
	void changePage(QListWidgetItem *current, QListWidgetItem *previous);

private:
	void createIcons();

	QListWidget *contentsWidget;
	QStackedWidget *pagesWidget;
};

#endif // DEDICATEDSLAVE_UI_CONFIGDIALOG_H