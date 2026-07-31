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

#include "utils/tarslog.h"

GetRollLoggerFunc GetRollLogger;
GetTimeLoggerFunc GetTimeLogger;


//版本
bool g_isDebug = false;

extern "C"
{
    void initLoggerGetter(GetRollLoggerFunc pRollLog, GetTimeLoggerFunc pTimeLog)
    {
        GetRollLogger = pRollLog;
        GetTimeLogger = pTimeLog;
    }
}

long TNowMS()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long TNow()
{
    return TNowMS() / 1000;
}

