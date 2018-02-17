#include <dedicatedslave/data/data.h>

#include <QXmlStreamReader>
#include <QString>
#include <QDebug>
#include <QHash>
#include <iostream>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QList>
#include <QListIterator>
#include <QStringListIterator>
#include <QApplication>

// http://www.walletfox.com/course/qxmlstreamreaderexample.php
//static const QString dataFile = QApplication::applicationDirPath() + "/dbdata.db";

/*!
 * \brief DedicatedSlaveData class Logic Data Model
 * \param parent
 */
DedicatedSlaveData::DedicatedSlaveData(QObject *parent)
	: QObject(parent)
{
    qDebug() << "\tCalling 'DedicatedSlaveData' constructor...";

	// Init variables
	QString dataFile = QApplication::applicationDirPath() + "/dbdata.db";

	// Database Manager
	ds_dataDbMgr = new DbManager(dataFile);

	// Init data
	instHash = new QHash<QString, GameInstance*>;

	if (ds_dataDbMgr->isOpen()){
		if(!ds_dataDbMgr->hasTable()){
			ds_dataDbMgr->createTable();
			ds_dataDbMgr->deleteAllInst();
		}
        qInfo() << "\tDeserializating and loading data...";
		loadData();
        qInfo().nospace() << "\tData loaded (" << instHash->size() << ")";
		ds_dataDbMgr->printAllInst();
	}else{
		qDebug() << "Database is not open!";
	}

}

DedicatedSlaveData::~DedicatedSlaveData()
{}

void DedicatedSlaveData::loadData()
{
	QHashIterator<QString, QStringList> it = ds_dataDbMgr->deserializeData();
	while(it.hasNext()){
		it.next();
		QString instName = it.key();
		QStringList listProps = it.value();
		QString instGame;
        int instStatus;
		QStringListIterator i(listProps);
        while (i.hasNext()){
            instGame = i.next();
            instStatus = i.next().toInt();
        }
        GameInstance *gi = createInstModel(instName, instGame, instStatus);
		instHash->insert(instName, gi);
	}
}

DedicatedSlaveData::InstancesTypes DedicatedSlaveData::getInstanceType(QString type)
{
	if(type == "csgo")
		return InstancesTypes::CSGO;
	else if(type == "rust")
		return InstancesTypes::RUST;
	else
		return InstancesTypes::NO;
}

int DedicatedSlaveData::getAppId(InstancesTypes type)
{
	if(type == InstancesTypes::CSGO)
		return 740;
	else if(type == InstancesTypes::RUST)
		return 258550;
	else
		return -1;
}

GameInstance* DedicatedSlaveData::createInstModel(QString instanceName, QString game)
{
	if(game == "csgo")
		return new GameInstanceCSGO(instanceName, game);
	else if(game == "rust")
		return new GameInstanceRust(instanceName, game);
    else
    {
        qWarning() << "Invalid game, abstact instance was created!";
        return new GameInstance(instanceName, game);
    }
}

GameInstance* DedicatedSlaveData::createInstModel(QString instanceName, QString game, int status)
{
    if(game == "csgo")
        return new GameInstanceCSGO(instanceName, game, status);
    else if(game == "rust")
        return new GameInstanceRust(instanceName, game, status);
    else
    {
        qWarning() << "Invalid game, abstact instance was created!";
        return new GameInstance(instanceName, game, status);
    }
}

void DedicatedSlaveData::insertInst(QString instanceName, QString game){
	GameInstance *gi = createInstModel(instanceName, game);
    ds_dataDbMgr->insertInst(instanceName, game, gi->getStatus());
	instHash->insert(instanceName, gi);
}

GameInstance* DedicatedSlaveData::getInst(QString instanceName)
{
	return instHash->value(instanceName);
}

void DedicatedSlaveData::removeInst(QString instanceName){
//	qInfo() << "remove:" << instanceName;
	instHash->remove(instanceName);
	ds_dataDbMgr->deleteInst(instanceName);
//	QListIterator<GameInstance*> i(instList);
//	int index = 0;
//	while(i.hasNext()){
//	GameInstance *gi = i.next();
//	if(gi->getName() == instanceName){
//	qInfo() << gi->getName() << index;
//	instList.removeAt(index);
//	}
//	index++;
//	}
}

bool DedicatedSlaveData::hasInst(QString instanceName){
	return instHash->contains(instanceName);
}

QHashIterator<QString, GameInstance*> DedicatedSlaveData::listInst(){
	QHashIterator<QString, GameInstance*> it(*instHash);
//	while(it.hasNext()){
//	qInfo() << it.next().key();
//	}
//	it.toFront();
	return it;
}

//Writing and reading XML files with Qt - qxmlstreamwriter and qxmlstreamreader supported classes
void DedicatedSlaveData::SaveXMLFile(){

	QString filename = QFileDialog::getSaveFileName(Q_NULLPTR, tr("Save Xml"), ".", tr("Xml files (*.xml)"));
	QFile file(filename);
	file.open(QIODevice::WriteOnly);

	QXmlStreamWriter xmlWriter(&file);
	xmlWriter.setAutoFormatting(true);
	xmlWriter.writeStartDocument();
	xmlWriter.writeStartElement("LAMPS");
	xmlWriter.writeStartElement("LIGHT1");
	xmlWriter.writeTextElement("State", "statevalue" );
	xmlWriter.writeTextElement("Room", "roomvalue");
	xmlWriter.writeTextElement("Potencial", "potencialvalue");
	xmlWriter.writeEndElement();

	file.close();
}

void DedicatedSlaveData::restoreInstReadXMLFile(){
	QXmlStreamReader Rxml;

	QString filename = QFileDialog::getOpenFileName(Q_NULLPTR, tr("Open Xml"), ".", tr("Xml files (*.xml)"));

	QFile file(filename);
	if (!file.open(QFile::ReadOnly | QFile::Text)){
		std::cerr << "Error: Cannot read file " << qPrintable(filename)
				  << ": " << qPrintable(file.errorString())
				  << std::endl;
	}

	Rxml.setDevice(&file);
	Rxml.readNext();

	while(!Rxml.atEnd()){
		if(Rxml.isStartElement()){
			if(Rxml.name() == "LAMPS"){
				Rxml.readNext();
			}else if(Rxml.name() == "LIGHT1"){
				while(!Rxml.atEnd()){
					if(Rxml.isEndElement()){
						Rxml.readNext();
						break;
					}else if(Rxml.isCharacters()){
						Rxml.readNext();
					}else if(Rxml.isStartElement()){
						qDebug() << Rxml.name();
						if(Rxml.name() == "State"){
							//ReadStateElement();
						}else if(Rxml.name() == "Room"){
							ReadRoomElement(&Rxml);
						}else if(Rxml.name() == "Potencial"){
							//ReadPotencialElement();
						}
						Rxml.readNext();
					}else{
						Rxml.readNext();
					}
				}
			}
		}else{
			Rxml.readNext();
		}
		file.close();
		if (Rxml.hasError()){
			std::cerr << "Error: Failed to parse file "
					  << qPrintable(filename) << ": "
					  << qPrintable(Rxml.errorString()) << std::endl;
		}else if (file.error() != QFile::NoError){
			std::cerr << "Error: Cannot read file " << qPrintable(filename)
					  << ": " << qPrintable(file.errorString())
					  << std::endl;
		}
	}
}

//Example for Room Element
void DedicatedSlaveData::ReadRoomElement(QXmlStreamReader *Rxml){
	while(!Rxml->atEnd()){
		if(Rxml->isEndElement()){
			Rxml->readNext();
			break;
		}else if(Rxml->isStartElement()){
			QString roomelement = Rxml->readElementText(); //Get the xml value
			Rxml->readNext();
			break;
		}else if(Rxml->isCharacters()){
			Rxml->readNext();
		}else{
			Rxml->readNext();
		}
	}
}
