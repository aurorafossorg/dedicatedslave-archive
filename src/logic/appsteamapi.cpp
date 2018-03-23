#include <dedicatedslave/logic/app.h>
#include <dedicatedslave/logic/appsteamapi.h>
#include <dedicatedslave/logic/helperio.h>
#include <dedicatedslave/logic/helpersys.h>

DedicatedSlaveAppSteamApi::DedicatedSlaveAppSteamApi(const QString &dir, QObject *parent) : QObject(parent){    
    parentWin = qobject_cast<QObject*>(parent);
    if(parentWin != 0){ // After casting parent widget QMainWindow, need to check if is not null (Async)
		//qInfo() << dir;
    }
}

DedicatedSlaveAppSteamApi::~DedicatedSlaveAppSteamApi(){
    delete parentWin;
}

void DedicatedSlaveAppSteamApi::downloadSteamCmd(){
	#ifdef Q_OS_LINUX
        DedicatedSlave::helperio_instance->downloadFileUrl("http://media.steampowered.com/installer/steamcmd_linux.tar.gz");
	#elif defined(Q_OS_WIN32)
        DedicatedSlave::helperio_instance->downloadFileUrl("http://media.steampowered.com/installer/steamcmd.zip");
	#elif defined(Q_OS_MACOS)
        DedicatedSlave::helperio_instance->downloadFileUrl("http://media.steampowered.com/client/installer/steamcmd_osx.tar.gz");
	#endif
}

QString DedicatedSlaveAppSteamApi::getVerifyCmd(const QString &wdir, GameInstance *gi){
	// QString cmdD = QString("/bin/xterm -hold -e /bin/bash -l -c \"cd %1 && ./steamcmd.sh +login anonymous +force_install_dir ./etcinstances/%2 +app_update %3 validate +quit\"")
	QString cmdD = QString("/bin/xterm -e /bin/bash -l -c \"cd %1 && ./steamcmd.sh +login anonymous +force_install_dir ./etcinstances/%2 +app_update %3 validate +quit\"")
		.arg(wdir)
		.arg(gi->getNameId())
		.arg(gi->getGameAppId());

	// Hold Turn on the hold resource, i.e., xterm will not immediately destroy its window when the shell command completes. It will wait until you use the window manager to destroy/kill the window, or if you use the menu entries that send a signal, e.g., HUP or KILL.

// QString cmdExec = QString("/bin/xterm -c -hold -e /bin/bash -l -c \"cd %1 && ./steamcmd.sh +login anonymous +force_install_dir ./etcinstances/%2 +app_update %3 validate +quit\"")
// 			.arg(wdir)
// 			.arg(gi->getNameId())QString wdir = "/home/alex1a/ProgrammingFiles/dedicatedslave/build/debug/";
// 			.arg(gi->getGameAppId());
// 	QString cmdString = QString("cd %1 && ./steamcmd.sh +login anonymous +force_install_dir ./etcinstances/%2 +app_update %3 validate +quit")
// 			.arg(wdir)
// 			.arg(gi->getNameId())
// 			.arg(gi->getGameAppId());
// 	QString cmd2 = QString("/bin/xterm -c -hold -e /bin/bash -l -c \"ls\"");
// 	QString cmd3 = QString("/bin/bash -c '/bin/xterm -hold -e /bin/bash -l -c \"cd %1 && ./steamcmd.sh +login anonymous +force_install_dir ./etcinstances/%2 +app_update %3 validate +quit\"'")
// 			.arg(wdir)
// 			.arg(gi->getNameId())
// 			.arg(gi->getGameAppId());
// 	QString cmd4 = QString("/bin/xterm -e /bin/bash -l -c \"ls\"");
// 	QString cmd5 = QString("/bin/bash -c '%1'").arg(cmd3);
// 	QString cmdD = QString("/bin/xterm -hold -e /bin/bash -l -c \"cd %1 && ./steamcmd.sh +login anonymous +force_install_dir ./etcinstances/%2 +app_update %3 validate +quit\"")
// 		.arg(wdirhc)
// 		.arg(gi->getNameId())
// 		.arg(gi->getGameAppId());
	return cmdD;
}
