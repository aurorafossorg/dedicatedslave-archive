#ifndef DEDICATEDSLAVE_LOGIC_APP_H
#define DEDICATEDSLAVE_LOGIC_APP_H

#include <DedicatedSlave/logic/helperio.h>
#include <DedicatedSlave/logic/processmanager.h>
#include <DedicatedSlave/logic/helpersys.h>
#include <DedicatedSlave/logic/appsteamapi.h>
#include <DedicatedSlave/logic/config.h>

#include <QString>
#include <QTimer>
#include <QProcess>
#include <QObject>
#include <QByteArray>
#include <QTextEdit>
#include <QProgressBar>
#include <DedicatedSlave/data/data.h>

class DedicatedSlaveAppSteamApi;

class DedicatedSlaveApp : public QObject {
	Q_OBJECT
signals:
	void signal_verifyComplete(int existStatus);
public:
	explicit DedicatedSlaveApp(const QString &dir, QObject *parent = 0);
	~DedicatedSlaveApp();
	bool hasInst(QString instanceName);
	bool hasReadyInst(QString instanceName);
	void addInst(QString instanceName, QString game);
	void removeInst(QString instanceName, bool removeDir);
	QHashIterator<QString, GameInstance*> listInst();
	void verifyInst(QString instanceName);
	void verifyInstProgress(QString instanceName);
    void runInst(const QString &instanceName);
public slots:
	void slot_handleVerifyProgress();
	void slot_handleVerfiyFinished(int exitCode, QProcess::ExitStatus exitStatus);
	void slot_handleVerifyStarted();
	void slot_verify();
private:
	QObject *parentWin;
    QString _getRunWd(const QString &);
    QString _getRunCmd(const QString &, const QString &);
	QStringList _loadSettings(QString file);
	void _readyReadStandardOutput();
	void _readyReadStandardError();
	QString _steamcmdDir;
	QString _settingsDir;
	DedicatedSlaveAppSteamApi* _steamapi;
	DedicatedSlaveAppConfig* _config;
	DedicatedSlaveData* _data;
	DedicatedSlave::DedicatedSlaveProcMgr* _procmgr;
	QTextEdit* _tedit;
	QProgressBar* _pgbar = new QProgressBar();
	QProcess* _pid = new QProcess();
	QString _appDir;
};

#endif // DEDICATEDSLAVE_LOGIC_APP_H
