/***************************************************************************************
#  Copyright (c) 2018
#  All rights reserved
#
#  @author  :
#  @name    :
#  @file    :
#  @date    :
#  @describe:
#***************************************************************************************/

#pragma once

#include "Comm/ITableGame.h"

namespace game
{
    namespace config
    {
        class GameConfig;
    }
    namespace config
    {
        class PluginConfig;
    }
    namespace context
    {
        class Context;
    }
    namespace process
    {
        class Process;
    }
    namespace gameserver
    {
        class GameServer;
    }

    class GameRoot
    {
    public:
        /**
         *
        */
        GameRoot(int iInitMode, GameInitParam const &sInitParams);

        /**
         *
        */
        ~GameRoot();

    public:
        inline std::string const &roomid() const
        {
            return sParams.strRoomTableId;
        }

    public:
        GameInitParam const        sParams;

        config::GameConfig        *cfg; //玩法配置
        config::PluginConfig      *plg; //玩法配置
        context::Context          *con; //游戏上下文
        process::Process          *pro; //游戏处理
        gameserver::GameServer    *gs;  //游戏通信句柄
    };
}
