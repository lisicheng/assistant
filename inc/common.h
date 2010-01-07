#ifndef COMMON_H
#define COMMON_H

#include "flogger.h"

#ifdef EKA2
const TUid KApplicationUid = { 0xa1986132 };
#else
const TUid KApplicationUid = { 0x100098e7 };
#endif

#define LOG(MSG) do {							\
	RFileLogger logger;						\
	logger.Connect();						\
	logger.CreateLog(_L("log"), _L("log"), EFileLoggingModeAppend);	\
	logger.Write(_L(MSG));						\
	logger.CloseLog();						\
	logger.Close();							\
} while(0);

#define LOGNUM(MSG) do {						\
	RFileLogger logger;						\
	logger.Connect();						\
	logger.CreateLog(_L("log"), _L("log"), EFileLoggingModeAppend);	\
	logger.WriteFormat(_L("%d"), MSG);				\
	logger.CloseLog();						\
	logger.Close();							\
} while(0);

#define LOGDES(MSG) do {						\
	RFileLogger logger;						\
	logger.Connect();						\
	logger.CreateLog(_L("log"), _L("log"), EFileLoggingModeAppend);	\
	logger.Write(MSG);						\
	logger.CloseLog();						\
	logger.Close();							\
} while(0);

#endif /* COMMON_H */
