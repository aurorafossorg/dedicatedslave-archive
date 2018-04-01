#ifndef APPSTEAMAPI_H
#define APPSTEAMAPI_H

#include <DedicatedSlave/logic/app.h>
#include <DedicatedSlave/data/models.h>
#include <DedicatedSlave/logic/helperio.h>
#include <DedicatedSlave/logic/helpersys.h>

#include <QString>
#include <QObject>
#include <QDebug>

class DedicatedSlaveAppSteamApi : public QObject {
	Q_OBJECT
public:
	explicit DedicatedSlaveAppSteamApi(const QString &dir, QObject *parent = 0);
	~DedicatedSlaveAppSteamApi();
	void downloadSteamCmd();
    QString getVerifyCmd(const QString &, GameInstance *gi);
private:
	QObject *parentWin;
};

#endif // APPSTEAMAPI_H
