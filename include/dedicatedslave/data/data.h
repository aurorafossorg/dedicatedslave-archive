#ifndef DATA_H
#define DATA_H

#include <dedicatedslave/data/dbmanager.h>
#include <dedicatedslave/data/models.h>
#include <QObject>
#include <QXmlStreamReader>
#include <QSqlDatabase>
#include <QHashIterator>

class DedicatedSlaveData : public QObject{

    Q_OBJECT
public:
    explicit DedicatedSlaveData(QObject *parent = 0);
    ~DedicatedSlaveData();
    void SaveXMLFile();
    void restoreInstReadXMLFile();
    enum InstancesTypes {
        CSGO = 0x00,
        RUST = 0x01,
        NO
    };
    Q_ENUM (InstancesTypes);
    InstancesTypes getInstanceType(QString type);
    void insertInst(QString instanceName, QString game);
    void removeInst(QString instanceName);
    bool hasInst(QString instanceName);
    QHashIterator<QString, GameInstance*> listInst();
    int getAppId(InstancesTypes type);
    GameInstance* getInst(QString instanceName);
private:
    GameInstance* createInstModel(QString instanceName, QString game);
    GameInstance* createInstModel(QString instanceName, QString game, int status);
    void loadData();
    DbManager *ds_dataDbMgr;
    QHash<QString, GameInstance*> *instHash;
    QVector<QString> getSubDir(QString dir);
    void ReadRoomElement(QXmlStreamReader *Rxml);
};

#endif // DATA_H
