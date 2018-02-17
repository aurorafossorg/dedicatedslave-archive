#ifndef APPSTEAMAPI_H
#define APPSTEAMAPI_H

#include <dedicatedslave/logic/app.h>
#include <dedicatedslave/data/models.h>
#include <dedicatedslave/logic/helperio.h>
#include <dedicatedslave/logic/helpersys.h>

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
