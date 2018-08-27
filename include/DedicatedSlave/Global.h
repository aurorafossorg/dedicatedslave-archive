#ifndef DEDICATEDSLAVE_GLOBAL_H
#define DEDICATEDSLAVE_GLOBAL_H

#pragma once

#ifndef DEDICATEDSLAVE_
#define DEDICATEDSLAVE_
#endif // DEDICATEDSLAVE_

#ifdef _WIN32
	#ifdef DEDICATEDSLAVE__COMPILING
		#define DSLAVE_API __declspec(dllexport)
	#else
		#define DSLAVE_API __declspec(dllimport)
	#endif // DEDICATEDSLAVE__COMPILING
#else
	#define DSLAVE_API
#endif // _WIN32

#endif // DEDICATEDSLAVE_GLOBAL_H
