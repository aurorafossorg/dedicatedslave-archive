#include <dedicatedslave/logic/app.h>
#include <dedicatedslave/logic/processmanager.h>
#include <dedicatedslave/logic/helperio.h>
#include <dedicatedslave/logic/helpersys.h>
#include <dedicatedslave/logic/config.h>

#include <QDebug>
#include <QTimer>
#include <QDir>
#include <QByteArray>
#include <QProcess>
#include <QTextEdit>
#include <QSettings>
#include <QProgressBar>

DedicatedSlaveApp::DedicatedSlaveApp(const QString &dir, QObject *parent)
	: QObject(parent),
	_steamapi(new DedicatedSlaveAppSteamApi(dir, this)),
	_config(new DedicatedSlaveAppConfig(dir, this)),
	_data(new DedicatedSlaveData(this)),
    _procmgr(new DedicatedSlave::DedicatedSlaveProcMgr())
{
//	qInfo() << "App:" << dir;
//	QApplication::applicationDirPath()
	parentWin = qobject_cast<QObject*>(parent);
    if(parentWin != 0){ // After casting parent widget QMainWindow, need to check if is not null (Async)
		QString _steamcmdFilename = "steamcmd_linux.tar.gz";
		QString _settingsFilename = "settings.ini";
        //qInfo() << "\tcurrentPath:" << QDir::currentPath();
		_appDir = dir;
		_steamcmdDir = "/" + _steamcmdFilename;
		_settingsDir = "/" + _settingsFilename;
		QString _steamcmdFullDir = _appDir + _steamcmdDir;
		QString _settingsFullDir = _appDir + _settingsDir;
		QString _steamcmdRelativeDir = "." + _steamcmdDir;
		QString _settingsRelativeDir = "." + _settingsDir;

		// System
        //DedicatedSlave::HelperSys::getInfo();
		qInfo() << "(S)\tLoading settings:" << _settingsFullDir;
		_config = new DedicatedSlaveAppConfig(_appDir, this);
		_config->saveSettings(_settingsRelativeDir);
		_config->saveSettingsValue(_settingsRelativeDir, "appDir", _appDir);
		QStringList list = _config->loadSettings(_settingsRelativeDir);
		foreach (QString cfgString, list) {
            qInfo() << "(S)\tSetting:" << cfgString;
		}

		// Init Data
		qInfo() << "(CLASS)\tInitializing 'DedicatedSlaveData' class...";
		_data = new DedicatedSlaveData(this);
		qInfo() << "(CLASS)\t'DedicatedSlaveData' initialized.";

		// TODO: VERIFY IF PRESENCE OF ANY FOLDER IN ETCINSTNACES THAT ARE NOT IN DB

		// SteamCMD Verification
        if(!DedicatedSlave::helperio_instance->existsFile(_steamcmdFullDir)){
            _steamapi->downloadSteamCmd();
		}

		// Extract if needed
//        if(!DedicatedSlave::helperio_instance->existsFile("./steamcmd.sh") || !DedicatedSlave::helperio_instance->existsFile("./steam.sh")){
//            qInfo() << "\tTrying to extract..." << _steamcmdFullDir;
//            DedicatedSlave::helperio_instance->uncompressTarGz(_steamcmdFullDir);
//		}
		// Create folders
		QDir dira("./etcinstances");
		if (!dira.exists()) {
			dira.mkpath(".");
		}

        //data->restoreInstReadXMLFile();
	}
}

DedicatedSlaveApp::~DedicatedSlaveApp(){

}

QHashIterator<QString, GameInstance*> DedicatedSlaveApp::listInst(){
	return _data->listInst();
}

bool DedicatedSlaveApp::hasReadyInst(QString instanceName){
	if(_data->getInst(instanceName)->getStatus() != -3){
		return true;
	}else{
		return false;
	}
}

bool DedicatedSlaveApp::hasInst(QString instanceName)
{
	return _data->hasInst(instanceName);
}

void DedicatedSlaveApp::addInst(QString instanceName, QString game)
{
	_data->insertInst(instanceName, game);
}

void DedicatedSlaveApp::removeInst(QString instanceName, bool removeDir)
{
	_data->removeInst(instanceName);
	if(removeDir){
		DedicatedSlave::helperio_instance->removeDirRec(QString("./etcinstances/%1").arg(instanceName));
	}
}

void DedicatedSlaveApp::runInst(const QString &instanceName){
	QStringList list;
	list.clear();
	list << "PATH=/opt:/opt/p:/bin:";
	_pid->setEnvironment(list);
	//    _pid->setWorkingDirectory("sadsa");
    QString wdir = _getRunWd(instanceName);
    QString cmd = _getRunCmd(wdir, instanceName);
	_pid->startDetached(cmd);
	_data->getInst(instanceName)->setStatus(1);
}

QString DedicatedSlaveApp::_getRunWd(const QString &instanceName){
    QString wdir = QString("%1/etcinstances/%2")
        .arg(QDir::currentPath())
        .arg(instanceName);
    return wdir;
}

QString DedicatedSlaveApp::_getRunCmd(const QString &wdir, const QString &instanceName){
    QString cmd = QString("/bin/xterm -hold -e /bin/bash -l -c \"cd %1 && ./%2\"")
        .arg(wdir)
        .arg(_data->getInst(instanceName)->getBinFilename());
    return cmd;
}

void DedicatedSlaveApp::slot_verify(){
	emit signal_verifyComplete(0);
}

void DedicatedSlaveApp::verifyInstProgress(QString instanceName){
	GameInstance *gi = _data->getInst(instanceName);
	//_steamapi->verifyInstProgress(gi);
    //QString wdir = "/home/alex1a/ProgrammingFiles/dedicatedslave/build/debug/";
	QString c = _steamapi->getVerifyCmd(_appDir, gi);
	QStringList list;
	list.clear();
	list << "PATH=/opt:/opt/p:/bin:";
	//_procmgr->setWorkingDir(instanceName, list);
	qInfo() << "cmd: " << c;
	//c = "/bin/bash -c \"ls\"";
	//QProcess *p = _procmgr->verifyInst(instanceName, c);
	_procmgr->addProcess(instanceName);
	QProcess *p = _procmgr->getProcess(instanceName);
	if(p == 0){
		qInfo() << "error process";
	}
	connect(p, QOverload<int,
	QProcess::ExitStatus>::of(&QProcess::finished),
		[=](int exitCode, QProcess::ExitStatus exitStatus){
			qInfo() << "Exit code:" << exitCode;
			qInfo() << "Exit status:" << exitStatus;
			if(exitCode == 0 && exitCode == QProcess::ExitStatus::NormalExit){
                qInfo() << "Setting status -2";
				gi->setStatus(-2);
			}
	});
	connect(p, &QProcess::started, [=](){
		qInfo() << "Proc started...";
        qInfo() << (QProcess::Running == p->state());
        qInfo() << (QProcess::Running == _procmgr->state(instanceName));
    });
//	connect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(slot_handleVerifyProgress())); // BEST
//	connect(p, SIGNAL(started()), this, SLOT(slot_handleVerifyStarted())); // BEST
//	connect(p, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(slot_handleVerfiyFinished(int, QProcess::ExitStatus)));

    p->start(c);
    qInfo() << (QProcess::Running == p->state());
    qInfo() << (QProcess::Running == _procmgr->state(instanceName));
    //_tedit = new QTextEdit;
    //_tedit->setFixedHeight(300);
    //_tedit->setFixedWidth(800);
//		connect(_pid, SIGNAL(readyRead()), this, SLOT(readProc()));
    // connect(_pid, SIGNAL(readyReadStandardOutput()), this, SLOT(slot_handleVerifyProgress())); // BEST
//		connect(_pid, &QProcess::readyReadStandardOutput, [=](){ _tedit->append(_pid->readAllStandardOutput()); });
//		connect(_pid, &QProcess::readyRead, [=](){ _tedit->append(_pid->readLine()); });
//		_tedit->show();
}

void DedicatedSlaveApp::slot_handleVerfiyFinished(int exitCode, QProcess::ExitStatus exitStatus){
	_pgbar->setValue(0);
	_pgbar->repaint();
	_pgbar->hide();
	qInfo() << "Exit code:" << exitCode;
	qInfo() << "Exit status:" << exitStatus;
}

void DedicatedSlaveApp::slot_handleVerifyStarted(){
	_pgbar->show();
}

void DedicatedSlaveApp::slot_handleVerifyProgress(){
	_pid->setReadChannel(QProcess::StandardOutput);
	//    while (_pid->canReadLine()){
	//       QString line = QString::fromLocal8Bit(_pid->readLine());
	//       QString line = QString::fromLocal8Bit(_pid->readAllStandardOutput());
	//    }
	QByteArray procOutput = _pid->readAllStandardOutput();
	QByteArray procError = _pid->readAllStandardError();
	QStringList strProcOutput = QString(procOutput).split("\n");
	QStringList strProcError = QString(procError).split("\n");
	foreach (QString line, strProcOutput){
		if(line.size() >= 63){
			if(line.contains("Update state (0x5) validating, progress:")){
				QString valueS = line.mid(42, 2);
				int value = valueS.toInt();
//                qInfo() << "valueS" << valueS;
//                qInfo() << "value" << value;
//                qInfo() << "line" << line;
//                qInfo() << "line.size" << line.size();
				_pgbar->setValue(value);
				_pgbar->repaint();
			}
		}

	}
}
