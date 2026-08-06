
#pragma once

#include<vector>

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace clientlogic
        {
            void TestBegin(long uid, const vector<char> &vecMsgData, GameRoot *root);
        }
    }
}
