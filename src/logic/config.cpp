#include <dedicatedslave/logic/config.h>

DedicatedSlaveAppConfig::DedicatedSlaveAppConfig(const QString &dir, QObject *parent) : QObject(parent){

}

DedicatedSlaveAppConfig::~DedicatedSlaveAppConfig(){

}

QStringList DedicatedSlaveAppConfig::loadSettings(QString file){
    QSettings settings(file, QSettings::NativeFormat);
	QString settingsText = settings.value("appdir", "").toString();
	QStringList list;
	list.clear();
	list.append(settingsText);
	return list;
}

void DedicatedSlaveAppConfig::saveSettings(const QString &file){
	QSettings settings(file, QSettings::NativeFormat);
	settings.setValue("appdir", ".");
	settings.setValue("appdir2", ".");
}

void DedicatedSlaveAppConfig::saveSettingsValue(const QString &file, const QString &key, const QString &value){
	QSettings settings(file, QSettings::NativeFormat);
	settings.setValue(key, value);
}
