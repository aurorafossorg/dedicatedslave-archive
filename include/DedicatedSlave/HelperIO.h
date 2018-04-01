#ifndef DEDICATEDSLAVE_HELPERIO_H
#define DEDICATEDSLAVE_HELPERIO_H

#pragma once

#include <DedicatedSlave/Global.h>

#include <memory>

namespace DedicatedSlave {
	class DSLAVE_API HelperIO {
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
	private:
		QNetworkAccessManager manager;
		QList<QNetworkReply *> currentDownloads;

	};

	static std::shared_ptr<HelperIO> helperio_instance(new HelperIO());
}

#endif // DEDICATEDSLAVE_HELPERIO_H
