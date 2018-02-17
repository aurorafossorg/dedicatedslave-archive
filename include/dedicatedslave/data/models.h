#ifndef MODELS_H
#define MODELS_H

#include <QString>
#include <QObject>
#include <QDateTime>

// GAMEINSTANCE

class GameInstance{
public:
    GameInstance(QString name, QString game);
    GameInstance(QString name, QString game, int status);
    QString getNameId();
    QString getGameId();
    int getGameAppId();
    int getStatus();
    int getNumPlayers();
    QString getServerName();
    void setStatus(int status);
    QDateTime getCreationDate();
    QString getBinFilename();
// Raising access levels of inherited class to derived class.
protected:
    int gameAppId;
    QString binFilename;
private:
    QString instCmd;
    QDateTime creationDate;
    QString nameId;
    QString gameId;
    QString serverName;
    int numPlayers;
    int status; // -3: not ready, -2 ready, -1 crashed, 0 stopped, 1 running
};

// CSGO

class GameInstanceCSGO : public GameInstance{

    public:
        GameInstanceCSGO(QString name, QString game);
        GameInstanceCSGO(QString name, QString game, int status);

};

// RUST

class GameInstanceRust : public GameInstance{

    public:
        GameInstanceRust(QString name, QString game);
        GameInstanceRust(QString name, QString game, int status);

};

#endif // MODELS_H
