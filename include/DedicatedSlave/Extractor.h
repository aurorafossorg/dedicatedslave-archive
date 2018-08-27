#ifndef DEDICATEDSLAVE_EXTRACTOR_H
#define DEDICATEDSLAVE_EXTRACTOR_H

#pragma once

#include <DedicatedSlave/Global.h>

namespace DedicatedSlave {
	struct DSLAVE_API ExtractorInstance {
		bool state = false;
	};


	class DSLAVE_API Extractor {
	public:
		Extractor();


	private:
		std::set<ExtractorInstance*> _instances;
	};
}

#endif // DEDICATEDSLAVE_EXTRACTOR_H