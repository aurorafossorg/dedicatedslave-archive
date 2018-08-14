#ifndef DEDICATEDSLAVE_UI_CONFIGDIALOG_H
#define DEDICATEDSLAVE_UI_CONFIGDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedWidget>
#include <dedicatedslave/logic/app.h>

class ConfigDialog : public QDialog {
	Q_OBJECT
public:
	ConfigDialog(DedicatedSlaveApp *app);
    QString getDirSteamcmd();
    QString getDirApp();
    QString getDirSettings();
    bool hasSteamcmd();
public slots:
    void instalSteamcmd();
	void changePage(QListWidgetItem *current, QListWidgetItem *previous);
private:
	void createIcons();
    bool _hasSteamcmd;
    DedicatedSlaveApp *_app;
    QString _dirSteamcmd;
    QString _dirApp;
    QString _dirSettings;
	QListWidget *contentsWidget;
	QStackedWidget *pagesWidget;
};

#endif // DEDICATEDSLAVE_UI_CONFIGDIALOG_H
