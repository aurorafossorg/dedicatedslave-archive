#ifndef DEDICATEDSLAVE_LOGIC_HELPERIO_H
#define DEDICATEDSLAVE_LOGIC_HELPERIO_H

#include <QNetworkAccessManager>
#include <QList>
#include <QUrl>
#include <QObject>
#include <QSharedPointer>
#include <QProcess>

namespace DedicatedSlave {
	class HelperIO : public QObject {
	Q_OBJECT
	private:
		QNetworkAccessManager manager;
		QList<QNetworkReply *> currentDownloads;
		QProcess* _pid = new QProcess();
	public:
		HelperIO();
        ~HelperIO();
		QString saveFileName(const QUrl &url);
		void removeDirRec(const QString &dirName);
		bool fileExists(QString path);
		bool saveToDisk(const QString &filename, QIODevice *data);
		void extractTarGz(QString );
	public slots:
		QString downloadFileUrl(QString urld);
		void downloadFinished(QNetworkReply *reply);
		void sslErrors(const QList<QSslError> &errors);
	};

	static QSharedPointer<HelperIO> helperio_instance(new HelperIO());
}

#endif // DEDICATEDSLAVE_LOGIC_HELPERIO_H
