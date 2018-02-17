#ifndef DEDICATEDSLAVELIB_GLOBAL_H
#define DEDICATEDSLAVELIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DEDICATEDSLAVELIB_LIBRARY)
	#define DEDICATEDSLAVELIBSHARED_EXPORT Q_DECL_EXPORT
#else
	#define DEDICATEDSLAVELIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DEDICATEDSLAVELIB_GLOBAL_H