
#pragma once

#include<vector>

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace clientlogic
        {
            void TokenBet(long uid, const vector<char> &vecMsgData, GameRoot *root,  bool Uop = true, bool left = false, string err_msg="", bool fromAI = false);
        }
    }
}

