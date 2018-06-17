#include <dedicatedslave/logic/processmanager.h>

namespace DedicatedSlave {
	DedicatedSlaveProcMgr::DedicatedSlaveProcMgr(){
		
	}

	DedicatedSlaveProcMgr::~DedicatedSlaveProcMgr(){
		while(count() != 0){
			delete _ptree.last();
			_ptree.remove(_ptree.lastKey());
		}
	}

	QProcess* DedicatedSlaveProcMgr::verifyInst(const QString &name, const QString &cmd){
		QProcess *proc = new QProcess(this);
		_ptree.insert(name, proc);
		if(_ptree.value(name)->startDetached(cmd)){
			return _ptree.value(name);
		}else{
			return 0;
		}
	}

	void DedicatedSlaveProcMgr::setWorkingDir(const QString &name, const QString &dir){
		_ptree.value(name)->setWorkingDirectory(dir);
	}

	void DedicatedSlaveProcMgr::setEnvironment(const QString &name, const QStringList &envlist){
		_ptree.value(name)->setEnvironment(envlist);
	}

	bool DedicatedSlaveProcMgr::isRunning(const QString &name) const{
		return (QProcess::Running == _ptree.value(name)->state());
	}

	QProcess::ProcessState DedicatedSlaveProcMgr::state(const QString &name) const{
		return _ptree.value(name)->state();
	}

	void DedicatedSlaveProcMgr::run(const QString &name, const QString &cmd){
		_ptree.value(name)->start(cmd);
	}

	void DedicatedSlaveProcMgr::run(const QString &name, const QString &program, const QStringList &args){
		_ptree.value(name)->start(program, args);
	}

	QString DedicatedSlaveProcMgr::getProgram(const QString &name) const{
		return _ptree.value(name)->program();
	}

	QStringList DedicatedSlaveProcMgr::getArguments(const QString &name) const{
		return _ptree.value(name)->arguments();
	}

	void DedicatedSlaveProcMgr::setArguments(const QString &name, const QStringList &args){
		_ptree.value(name)->setArguments(args);
	}

	void DedicatedSlaveProcMgr::setProgram(const QString &name, const QString &program){
		_ptree.value(name)->setProgram(program);
	}
}
