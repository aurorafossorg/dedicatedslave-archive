#include <dedicatedslave/data/models.h>
#include <QDebug>

// GameInstance

GameInstance::GameInstance(QString name, QString game){
    qDebug() << "\tCalling 'GameInstance' constructor...";
    nameId = name;
    gameId = game;
    creationDate = QDateTime::currentDateTime();
    instCmd = "";
    status = -3;
    numPlayers = 10;
    serverName = "[DedicatedSlave] " + name + "'s Server";
}

GameInstance::GameInstance(QString name, QString game, int status){
    qDebug() << "\tCalling 'GameInstance' constructor...";
    nameId = name;
    gameId = game;
    creationDate = QDateTime::currentDateTime();
    instCmd = "";
    this->status = status;
    numPlayers = 10;
    serverName = "[DedicatedSlave] " + name + "'s Server";
}

QDateTime GameInstance::getCreationDate(){
    return creationDate;
}

QString GameInstance::getNameId(){
    return nameId;
}

QString GameInstance::getGameId(){
    return gameId;
}

int GameInstance::getGameAppId(){
    return gameAppId;
}

int GameInstance::getStatus(){
    return status;
}

int GameInstance::getNumPlayers(){
    return numPlayers;
}

QString GameInstance::getServerName(){
    return serverName;
}

void GameInstance::setStatus(int status){
    this->status = status;
}

QString GameInstance::getBinFilename(){
    return binFilename;
}

// GameInstanceCSGO

GameInstanceCSGO::GameInstanceCSGO(QString name, QString game) : GameInstance(name, game){
    qDebug() << "\tCalling 'GameInstanceCSGO' constructor...";
    this->gameAppId = 740;
    this->binFilename = "srcds_run";
}

GameInstanceCSGO::GameInstanceCSGO(QString name, QString game, int status) : GameInstance(name, game, status){
    qDebug() << "\tCalling 'GameInstanceCSGO' constructor...";
    this->gameAppId = 740;
    this->binFilename = "srcds_run";
}

// GameInstanceRust

GameInstanceRust::GameInstanceRust(QString name, QString game) : GameInstance(name, game){
    qDebug() << "\tCalling 'GameInstanceRust' constructor...";
    this->gameAppId = 258550;
    this->binFilename = "RustDedicated";
}

GameInstanceRust::GameInstanceRust(QString name, QString game, int status) : GameInstance(name, game, status){
    qDebug() << "\tCalling 'GameInstanceRust' constructor...";
    this->gameAppId = 258550;
    this->binFilename = "RustDedicated";
}
