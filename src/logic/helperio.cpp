//#include <QCoreApplication>
#include <dedicatedslave/logic/helperio.h>

#include <QFileInfo>
#include <QNetworkReply>
#include <QDir>

// https://stackoverflow.com/questions/4383864/downloading-file-in-qt-from-url
// http://www.antonioborondo.com/2014/10/22/zipping-and-unzipping-files-with-qt/
namespace DedicatedSlave {
	HelperIO::HelperIO()
	{
	//	this->connectSignalsAndSlots();
		connect(&manager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(downloadFinished(QNetworkReply*)));
	}

	HelperIO::~HelperIO(){
		delete _pid;
	}

	bool HelperIO::fileExists(QString path){
		QFileInfo check_file(path);
		// check if file exists and if yes: Is it really a file and no directory?
		if (check_file.exists() && check_file.isFile())
			return true;
		else
			return false;
	}

	void HelperIO::removeDirRec(const QString &dirName){
		QDir dir(dirName);
		dir.removeRecursively();
	}

	QString HelperIO::saveFileName(const QUrl &url){
		qDebug() << "URL: " << url;
		QString path = url.path();
		QString basename = QFileInfo(path).fileName();

		if (basename.isEmpty())
			basename = "download";

		if (QFile::exists(basename)) {
			// already exists, don't overwrite
			int i = 0;
			basename += '.';
			while (QFile::exists(basename + QString::number(i)))
				++i;

			basename += QString::number(i);
		}
		return basename;
	}

	bool HelperIO::saveToDisk(const QString &filename, QIODevice *data){
		qDebug() << filename;
		QFile file(filename);
		if (!file.open(QIODevice::WriteOnly)) {
			fprintf(stderr, "Could not open %s for writing: %s\n",
					qPrintable(filename),
					qPrintable(file.errorString()));
			return false;
		}

		file.write(data->readAll());
		file.close();

		return true;
	}

	void HelperIO::sslErrors(const QList<QSslError> &sslErrors){
        #ifndef QT_NO_SSL
            foreach (const QSslError &error, sslErrors)
                fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
        #else
            Q_UNUSED(sslErrors);
        #endif
	}

	void HelperIO::downloadFinished(QNetworkReply *reply){
		qDebug() << "Reply: " << reply->isOpen();
		QUrl url = reply->url();
		if (reply->error()) {
            fprintf(stderr, "\tDownload of %s failed: %s\n", url.toEncoded().constData(), qPrintable(reply->errorString()));
		} else {
			QString filename = saveFileName(url);
            if (saveToDisk(filename, reply)){
                printf("\tDownload of %s succeeded (saved to %s)\n", url.toEncoded().constData(), qPrintable(filename));
            }
		}

		currentDownloads.removeAll(reply);
		reply->deleteLater();
		//	if (currentDownloads.isEmpty())
		//		// all downloads finished
		//		QCoreApplication::instance()->quit();
	}

    QString HelperIO::downloadFileUrl(QString urld){
		//qInfo() << "execute";
	//	QString urld = "http://media.steampowered.com/installer/steamcmd_linux.tar.gz";
		QUrl url = QUrl::fromEncoded(urld.toLocal8Bit());

        //qInfo() << "doDownload";
        QNetworkRequest request(url);
        //qInfo() << url.toString();
        QNetworkReply *reply = manager.get(request);

    //#ifndef QT_NO_SSL
    //	connect(reply, SIGNAL(sslErrors(QList<QSslError>)), SLOT(sslErrors(QList<QSslError>)));
    //#endif
        currentDownloads.append(reply);
        return url.path();

	}

	// TODO: Temporary approach to uncompress tar.gz file, include library
	void HelperIO::extractTarGz(QString file){
		QStringList list;
		list.clear();
		//list << "PATH=/opt:/opt/p:/bin:";
		_pid->setEnvironment(list);
		_pid->start(QString("tar -xvzf %1").arg(file));
		//_pid->waitForStarted();
	}
}
