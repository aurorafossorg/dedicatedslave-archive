#include <dedicatedslave/logic/helpersys.h>

// https://stackoverflow.com/questions/4383864/downloading-file-in-qt-from-url
// http://www.antonioborondo.com/2014/10/22/zipping-and-unzipping-files-with-qt/

namespace DedicatedSlave {
	void HelperSys::getInfo(){
        qDebug() << "\tcurrentCpuArchitecture():" << QSysInfo::currentCpuArchitecture();
        qDebug() << "\tproductType():" << QSysInfo::productType();
        qDebug() << "\tproductVersion():" << QSysInfo::productVersion();
        qDebug() << "\tprettyProductName():" << QSysInfo::prettyProductName();
	}
}
