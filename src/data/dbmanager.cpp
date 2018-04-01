#include <DedicatedSlave/data/dbmanager.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DbManager::DbManager(const QString& path){
   qDebug() << "\tCalling 'DbManager' constructor...";
   dbdata = QSqlDatabase::addDatabase("QSQLITE");
   dbdata.setDatabaseName(path);
   if (!dbdata.open()){
      qWarning() << "(DB)\tConnection error with database, fail to open";
   }else{
      qInfo().nospace() << "(DB)\tConnection ok (" << path << ")";
   }
}

DbManager::~DbManager(){
    if (dbdata.isOpen()){
        dbdata.close();
    }
}

bool DbManager::isOpen() const{
    return dbdata.isOpen();
}

QHashIterator<QString, QStringList> DbManager::deserializeData(){
    QHash<QString, QStringList> hash;
    hash.setSharable(false);
    QSqlQuery query("SELECT * FROM instances");
    int idName = query.record().indexOf("name");
    int idGame = query.record().indexOf("game");
    int idStatus = query.record().indexOf("status");
    while (query.next()){
        QStringList list;
        QString name = query.value(idName).toString();
        QString game = query.value(idGame).toString();
        int status = query.value(idStatus).toInt();
        list.append(game);
        list.append(QString::number(status));
        hash.insert(name, list);
    }
    QHashIterator<QString, QStringList> it(hash);
//    while(it.hasNext()){
//        qInfo() << "blabla" << it.next().key();
//    }
//    it.toFront();
    return it;
}

bool DbManager::createTable(){
    bool success = false;
    QSqlQuery query;
    query.prepare("CREATE TABLE instances(id INTEGER PRIMARY KEY, name TEXT, game TEXT, status INTEGER);");
    if (!query.exec()){
        qDebug() << "\tCouldn't create the table 'instances': one might already exist.";
//        QSqlQuery query;
//        query.prepare("DROP TABLE instances;");
//        query.exec();ed (0) (.
        success = false;
    }
    return success;
}

bool DbManager::dropTable(){
    bool success = false;
    QSqlQuery query;
    query.prepare("DROP TABLE instances;");
    if (!query.exec()){
        qDebug() << "Couldn't drop the table 'instances'.";
        success = false;
    }
    return success;
}

bool DbManager::hasTable(){
    bool success = false;
    QSqlQuery query;
    query.prepare("CREATE TABLE instances(rowid INTEGER PRIMARY KEY);");
    if(!query.exec()){
        qDebug() << "\tCouln't create the table 'instances': one might already exist.";
        success = true;
    }else{
        QSqlQuery querya;
        querya.prepare("DROP TABLE instances;");
        if(!querya.exec()){
            success = true;
        }
    }
    return success;
}

bool DbManager::insertInst(const QString &name, const QString &game, const int &status){
   bool success = false;
   // you should check if args are ok first...
   QSqlQuery query;
   query.prepare("INSERT INTO instances (id, name, game, status) "
                 "VALUES (NULL, (:name), (:game), (:status))");
   query.bindValue(":name", name);
   query.bindValue(":game", game);
   query.bindValue(":status", status);
   if(query.exec()){
       success = true;
   }else{
        qWarning() << "insertInst error:  "
                 << query.lastError()
                 << query.lastError().type();
   }
   return success;
}

bool DbManager::deleteInst(const QString& name){
    bool success = false;
    if (hasInstance(name)){
        QSqlQuery queryDelete;
        queryDelete.prepare("DELETE FROM instances WHERE name = (:name)");
        queryDelete.bindValue(":name", name);
        success = queryDelete.exec();
        if(!success){
            qWarning() << "removeInstance failed: " << queryDelete.lastError();
        }
    }else{
        qWarning() << "removeInstance failed: person doesnt exist";
    }
    return success;
}

void DbManager::deleteAllInst(){
    QSqlQuery query;
    query.prepare("DELETE FROM instances");
    query.exec();
}

bool DbManager::hasInstance(const QString& name) const{
    bool exists = false;
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT name FROM instances WHERE name = (:name)");
    checkQuery.bindValue(":name", name);
    if (checkQuery.exec()){
        if (checkQuery.next()){
            exists = true;
        }
    }else{
        qDebug() << "instance exists failed: " << checkQuery.lastError();
    }
    return exists;
}

void DbManager::printAllInst() const{
    qInfo() << "\tInstances in db:";
    QSqlQuery query("SELECT * FROM instances");
    int idName = query.record().indexOf("name");
    int idGame = query.record().indexOf("game");
    while (query.next()){
        QString name = query.value(idName).toString();
        QString game = query.value(idGame).toString();
        qInfo().nospace() << "\t\t\t- " << name << "(" << game << ")";
    }
}
