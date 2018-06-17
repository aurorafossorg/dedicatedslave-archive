//#include <QCoreApplication>
#include <dedicatedslave/logic/helperio.h>

#include <QFileInfo>
#include <QNetworkReply>
#include <QDir>

namespace DedicatedSlave {
	HelperIO::HelperIO(){
//		this->connectSignalsAndSlots();
		connect(&manager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(downloadFinished(QNetworkReply*)));
	}

	HelperIO::~HelperIO(){
		delete _pid;
	}

    bool HelperIO::existsFile(QString path){
		QFileInfo check_file(path);
        if (check_file.exists() && check_file.isFile()){ // check if file exists and if yes: Is it really a file and no directory?
            return true;
        } else {
            return false;
        }
	}

    bool HelperIO::existsDir(QString path){
        return false;
    }

	void HelperIO::removeDirRec(const QString &dirName){
		QDir dir(dirName);
		dir.removeRecursively();
	}

	QString HelperIO::saveFileName(const QUrl &url){
		QString path = url.path();
		QString basename = QFileInfo(path).fileName();
        if (basename.isEmpty()){
            basename = "download";
        }
        if (QFile::exists(basename)) { // already exists, don't overwrite
			int i = 0;
			basename += '.';
            while (QFile::exists(basename + QString::number(i))){
                ++i;
            }
			basename += QString::number(i);
		}
		return basename;
	}

	bool HelperIO::saveToDisk(const QString &filename, QIODevice *data){
		QFile file(filename);
		if (!file.open(QIODevice::WriteOnly)) {
            fprintf(stderr, "Could not open %s for writing: %s\n", qPrintable(filename), qPrintable(file.errorString()));
			return false;
		}
		file.write(data->readAll());
		file.close();
		return true;
	}

	void HelperIO::sslErrors(const QList<QSslError> &sslErrors){
        #ifndef QT_NO_SSL
            foreach (const QSslError &error, sslErrors){
                fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
            }
        #else
            Q_UNUSED(sslErrors);
        #endif
	}

	void HelperIO::downloadFinished(QNetworkReply *reply){
		QUrl url = reply->url();
		if (reply->error()) {
            fprintf(stderr, "\tDownload of %s failed: %s\n", url.toEncoded().constData(), qPrintable(reply->errorString()));
		} else {
			QString filename = saveFileName(url);
            if (saveToDisk(filename, reply)){
                QString currentPath = QDir::currentPath();
                QString fullPath = currentPath + "/" + filename;
                //qDebug() << "\tReply isOpen(): " << reply->isOpen();
                //qDebug() << "\tReply isRunning(): " << reply->isRunning();
                printf("\tDownload of %s succeeded (saved to %s)\n", url.toEncoded().constData(), qPrintable(fullPath));
                uncompressTarGz(fullPath);
            }
		}
		currentDownloads.removeAll(reply);
		reply->deleteLater();
        if (currentDownloads.isEmpty()){
            //qDebug() << "\tAll downloads are finished";
        }
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
    void HelperIO::uncompressTarGz(QString file){
		QStringList list;
		list.clear();
		//list << "PATH=/opt:/opt/p:/bin:";
		_pid->setEnvironment(list);
		_pid->start(QString("tar -xvzf %1").arg(file));
        printf("\tExtraction complete... %s\n", qPrintable(file));
		//_pid->waitForStarted();
	}

    void HelperIO::compressZip(QString filename, QString zipFilename){
        QFile infile(filename);
        QFile outfile(zipFilename);
        infile.open(QIODevice::ReadOnly);
        outfile.open(QIODevice::WriteOnly);
        QByteArray uncompressed_data = infile.readAll();
        QByteArray compressed_data = qCompress(uncompressed_data, 9);
        outfile.write(compressed_data);
        infile.close();
        outfile.close();
    }

    void HelperIO::uncompressZip(QString zipFilename, QString filename){
        QFile infile(zipFilename);
        QFile outfile(filename);
        infile.open(QIODevice::ReadOnly);
        outfile.open(QIODevice::WriteOnly);
        QByteArray uncompressed_data = infile.readAll();
        QByteArray compressed_data = qUncompress(uncompressed_data);
        outfile.write(compressed_data);
        infile.close();
        outfile.close();
    }
}
