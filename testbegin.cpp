#include "common/macros.h"
#include "common/nndef.h"
#include "common/nnlogic.h"
#include "gameroot.h"
#include "logic/clientlogic/core/gamestation.h"
#include "utils/tarslog.h"
#include "context/context.h"
#include "config/gameconfig.h"
#include "suoha.pb.h"
#include "process/process.h"
#include "message/sendclientmessage.h"
#include "message/sendroommessage.h"
#include "logic/gamelogic/core/endtimer.h"
#include "CommonCode.pb.h"
#include "logic/gamelogic/core/checkbegin.h"

using namespace nndef;

namespace game
{
    namespace logic
    {
        namespace clientlogic
        {
            void TestBegin(long uid, const vector<char> &vecMsgData, GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__
                using namespace RoomSo;
                using namespace context;
                using namespace process;
                using namespace config;
                using namespace message;
                using namespace nnlogic;
                using namespace gamelogic;

                //check game begin
                game::logic::gamelogic::CheckBegin(root);

                __CATCH__
                PERFSTATS_EXIT();
            }
        }
    }
}
