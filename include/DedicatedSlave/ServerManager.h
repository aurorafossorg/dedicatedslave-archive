#ifndef DEDICATEDSLAVE_SERVERMANAGER_H
#define DEDICATEDSLAVE_SERVERMANAGER_H

#pragma once

#include <DedicatedSlave/Global.h>

#include <DedicatedSlave/ServerInstance.h>

#include <set>
#include <memory>

namespace DedicatedSlave {
	class DSLAVE_API ServerManager {
	public:
		ServerManager();
		~ServerManager();
		void addServer(ServerInstance* );
		void removeServer(ServerInstance* );
		size_t count();

	private:
		std::set<ServerInstance*> _instances;
	};
}

#endif // DEDICATEDSLAVE_SERVERMANAGER_H