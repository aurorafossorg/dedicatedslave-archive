#ifndef DEDICATEDSLAVE_LOGIC_HELPERSYS_H
#define DEDICATEDSLAVE_LOGIC_HELPERSYS_H

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace DedicatedSlave {
	class HelperSys : public QObject {
	Q_OBJECT
	public:
		static void getInfo();
		static QString getOS();
	};

	inline QString HelperSys::getOS()
	{
		#if defined(Q_OS_ANDROID)
			return "android";
		#elif defined(Q_OS_BLACKBERRY)
			return "blackberry";
		#elif defined(Q_OS_IOS)
			return "ios";
		#elif defined(Q_OS_MACOS)
			return "macos";
		#elif defined(Q_OS_TVOS)
			return "tvos";
		#elif defined(Q_OS_WATCHOS)
			return "watchos";
		#elif defined(Q_OS_WINCE)
			return "wince";
		#elif defined(Q_OS_WIN)
			return "windows";
		#elif defined(Q_OS_LINUX)
			return "linux";
		#elif defined(Q_OS_UNIX)
			return "unix";
		#else
			return "unknown";
		#endif
	}
}

#endif // DEDICATEDSLAVE_LOGIC_HELPERSYS_H