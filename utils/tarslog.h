/***************************************************************************************
#  Copyright (c) 2019
#  All rights reserved
#
#  @author  :
#  @name    :
#  @file    :
#  @date    :
#  @describe:
#***************************************************************************************/

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#include "util/tc_logger.h"
#include "Comm/ITableGame.h"

//调试开关
extern bool g_isDebug;
//获取时间戳(毫秒)
extern long TNowMS();
//获取时间戳(秒)
extern long TNow();

/////////////////////////////////////////////////////////
//GameSo滚动日志 按天日志加个壳
#define LOG_FATAL(XXX)  (GAMEROLL_ERROR << "[FATAL]|" << __POS__ << XXX << endl)
#define LOG_ERROR(XXX)	(GAMEROLL_ERROR << "[ERROR]|" << __POS__ << XXX << endl)
#define LOG_WARN(XXX)	(GAMEROLL_WARN  << "[WARN] |" << __POS__ << XXX << endl)
#define LOG_INFO(XXX)	(GAMEROLL_INFO  << "[INFO] |" << __POS__ << XXX << endl)
#define LOG_DEBUG(XXX)	(GAMEROLL_DEBUG << "[DEBUG]|" << __POS__ << XXX << endl)
#define LOG_TRACE(XXX)	(GAMEROLL_DEBUG << "[TRACE]|" << __POS__ << XXX << endl)

///////////////////////////////////////////////////////////////
//GameSo按天日志、致命、异常、追踪   极端多或者极端少的日志
#define DLOG_FATAL(XXX) \
do {\
	if (true) {\
		FDLOG_FATAL << "[FATAL]|" <<  __POS__ << " " << XXX << endl;\
	}\
} while(0);

#define DLOG_EXCEPT(XXX)\
do {\
	if (true) {\
		FDLOG_EXCEPT << "[EXCEPT]|" <<  __POS__ << " " << XXX << endl;\
	}\
} while(0);

#define DLOG_TRACE(XXX)\
do {\
	if (g_isDebug) {\
		FDLOG_TRACE <<"["<< TNowMS() <<"]"<< "[TRACE]|" <<  __POS__ << " " << XXX << endl;\
	}\
} while(0);

#define PERFSTATS_ENTRY() \
long ts = TNowMS();\
do {\
	if (g_isDebug) {\
		FDLOG_TRACE << "[PERFSTATS]|" << __FUNCTION__ << "() enter: " << ts <<endl;\
	}\
} while(0);

#define PERFSTATS_EXIT()\
do {\
	if (g_isDebug) {\
		long diff = (TNowMS() - ts);\
		if (diff > 3) {\
			FDLOG_TRACE << "[PERFSTATS]|" << __FUNCTION__ << "() exit, costTime: " << diff << endl;\
		}\
	}\
} while(0);

#define PERFSTATS(XXX)\
do {\
	if (g_isDebug) {\
		FDLOG_TRACE << "[PERFSTATS]|" <<__FUNCTION__ << "() timer, " << XXX << endl;\
	}\
} while(0);

#define DLOG_ENTRY(in)\
do {\
	if (g_isDebug) {\
		FDLOG_ENTRY << "GameSo>>>> Enter >>>> " << __FUNCTION__ << "() in(" << in << ")" << endl;\
	}\
} while(0);

#define DLOG_EXIT(out, ret)\
do {\
	if (g_isDebug) {\
		FDLOG_EXIT << "GameSo<<<< Exit <<<< " << __FUNCTION__ << "() out[" << out << "], ret = " << ret << endl;\
	}\
} while(0);

#define DLOG_ROBOT(XXX)\
do {\
	if (g_isDebug) {\
		FDLOG_ROBOT << "[ROBOT] | " << XXX << endl;\
	}\
} while(0);

////////////////////////////////////////////////////////
//RoomServer日志,合并到RoomServer的日志中
#define RLOG_FATAL  ROOMLOG_ERROR << "[GAMESO_FATAL] | "
#define RLOG_ERROR	ROOMLOG_ERROR << "[GAMESO_ERROR] | "
#define RLOG_WARN	ROOMLOG_WARN  << "[GAMESO_WARN]  | "
#define RLOG_INFO	ROOMLOG_INFO  << "[GAMESO_INFO]  | "
#define RLOG_DEBUG	ROOMLOG_DEBUG << "[GAMESO_DEBUG] | "
#define RLOG_TRACE	ROOMLOG_DEBUG << "[GAMESO_TRACE] | "

/////////////////////////////////////////////////////
//日志对象Get函数
extern GetRollLoggerFunc GetRollLogger;
extern GetTimeLoggerFunc GetTimeLogger;

////////////////////////////////////////////////////
//RoomServer日志包装
#define ROLLINS        ((*GetRollLogger)()->logger())
#define ROOMLOG(level) (ROLLINS->level() << "[" << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << "] " )
#define ROOMLOG_DEBUG  (ROOMLOG(debug))
#define ROOMLOG_INFO   (ROOMLOG(info))
#define ROOMLOG_WARN   (ROOMLOG(warn))
#define ROOMLOG_ERROR  (ROOMLOG(error))

///////////////////////////////////////////////////
//DayLog ForGameSo日志包装
#define WIDE(wide,cfill) std::setw(wide) << std::setfill(cfill)
#define OCT(wide,cfill)  std::setw(wide) << std::setfill(cfill) << std::oct
#define W(wide)          std::setw(wide)

#define __DEF_NAME__
#define __filename__ (string(__FILE__).substr(string(__FILE__).find_last_of("/")+1))
#define __POS__  "[" << __filename__ << ":" << __LINE__ << ":" << __FUNCTION__ << "] |"

#define __LOGNAME(X,Y) X#Y
#define _LOGNAME(X,Y) __LOGNAME(X,Y)
#define LOGNAME(X) _LOGNAME(#X,__GAMEID__)

#define FDLOGINS(x)       ((*GetTimeLogger)(x))
#define FDLOG_FATAL       (FDLOGINS(LOGNAME(SoFatal_))->any())
#define FDLOG_EXCEPT      (FDLOGINS(LOGNAME(SoExcept_))->any())
#define FDLOG_TRACE       (FDLOGINS(LOGNAME(SoTrace_))->debug())
#define DLOG_TRACE_FLUSH  (FDLOGINS(LOGNAME(SoTrace_))->flush())
#define FDLOG_ROBOT       (FDLOGINS(LOGNAME(SoRobot_))->debug())

#define s1(x) #x
#define s2(x) s1(x)

#define GAMEROLL(level)  (FDLOGINS(LOGNAME(Roll_So))->level())
#define GAMEROLL_ERROR   (GAMEROLL(error))
#define GAMEROLL_WARN    (GAMEROLL(warn))
#define GAMEROLL_INFO    (GAMEROLL(info))
#define GAMEROLL_DEBUG   (GAMEROLL(debug))

//////////////////////////////////////////////////
//遍历输出数组

#define LOG_ASSERT(cond)\
if (!(cond))\
{\
    LOG_INFO("Assert #cond failed");\
}

#define LOG_VECTOR(ll,v)  \
{\
ostringstream s; \
s << #v" | contain : " ;\
for (unsigned int i = 0; i < v.size(); ++i)\
{\
    s << v[i] << " , " ;\
}\
ll( s.str());\
}


