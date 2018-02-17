#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>
#include <QSettings>

class DedicatedSlaveAppConfig : public QObject {
    Q_OBJECT
    public:
        DedicatedSlaveAppConfig(const QString &dir, QObject *parent = 0);
        ~DedicatedSlaveAppConfig();
        QStringList loadSettings(QString file);
        void saveSettings(const QString &);
        void saveSettingsValue(const QString &, const QString &, const QString &);
};

#endif // CONFIG_H
