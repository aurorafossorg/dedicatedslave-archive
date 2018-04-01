#ifndef DEDICATEDSLAVE_LOGIC_PROCESSMANAGER_H
#define DEDICATEDSLAVE_LOGIC_PROCESSMANAGER_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QString>
#include <QProcess>
#include <QDebug>
#include <QStringList>

namespace DedicatedSlave {
	class DedicatedSlaveProcMgr : public QObject {
	Q_OBJECT
	private:
		QMap<QString, QProcess*> _ptree;

//		void _runQueue();
//		void _checkQueue();

	public:
		DedicatedSlaveProcMgr();
		~DedicatedSlaveProcMgr();
		QProcess* verifyInst(const QString &, const QString &);
		void setWorkingDir(const QString &, const QString &);
		void setEnvironment(const QString &, const QStringList &);
		void run(const QString &, const QString &);
		void run(const QString &, const QString &, const QStringList &);
		bool isRunning(const QString &) const;
		QProcess::ProcessState state(const QString &) const;
		QString getProgram(const QString &) const;
		QStringList getArguments(const QString &) const;
		void setProgram(const QString &, const QString &);
		void setArguments(const QString &, const QStringList &);
		inline void addProcess(const QString &name, QProcess* proc = new QProcess()) { _ptree.insert(name, proc); }
		inline void removeProcess(const QString &name) { _ptree.remove(name); }
		inline QProcess* getProcess(const QString &name) const { return _ptree.value(name); }
		inline QList<QString> getProcessNameList() const { return _ptree.keys(); }
		inline QList<QProcess*> getProcessList() const { return _ptree.values(); }
		inline int count() const { return _ptree.size(); }

		static void runCLI(const QString &);
		static void runCLI(const QString &, const QStringList &);

		inline static int run(const QString &cmd) { return QProcess::execute(cmd); }
		inline static int run(const QString &p, const QStringList &args) { return QProcess::execute(p, args); }
		inline static bool runDetached(const QString &cmd) { return QProcess::startDetached(cmd); }
		inline static bool runDetached(const QString &p, const QStringList &args, const QString &wdir = QString(), qint64* pid = Q_NULLPTR)
		{ return QProcess::startDetached(p, args, wdir, pid); }

		inline static QStringList getSystemEnvironment() { return QProcess::systemEnvironment(); }
	};
}

#endif // DEDICATEDSLAVE_LOGIC_PROCESSMANAGER_H
