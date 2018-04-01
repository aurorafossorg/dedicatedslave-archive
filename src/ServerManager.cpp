#include <DedicatedSlave/ServerManager.h>

#include <algorithm>

namespace DedicatedSlave {
	ServerManager::ServerManager()
	{}

	void ServerManager::addServer(ServerInstance* instance)
	{
		_instances.insert(instance);
	}

	void ServerManager::removeServer(ServerInstance* instance)
	{
		_instances.erase(std::find(_instances.begin(), _instances.end(), instance));
	}
}