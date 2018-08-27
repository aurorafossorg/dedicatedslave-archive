#ifndef DEDICATEDSLAVE_DOWNLOADER_H
#define DEDICATEDSLAVE_DOWNLOADER_H

#pragma once

#include <DedicatedSlave/Global.h>

namespace DedicatedSlave {
	struct DSLAVE_API DownloadInstance {
		void* data;
		bool state = false;
		CURL* curlInstance;
	};

	class DSLAVE_API DownloadManager {
	public:
		DownloadManager();
		DownloadInstance* asyncDownload(std::string );
		void* download(std::string );
		void clear(DownloadInstance*);

	private:
		std::set<DownloadInstance*> _instances;
	};
}

#endif // DEDICATEDSLAVE_DOWNLOADER_H