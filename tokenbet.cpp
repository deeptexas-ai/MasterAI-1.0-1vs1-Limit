#include "common/macros.h"
#include "common/nndef.h"
#include "gameroot.h"
#include "logic/clientlogic/core/tokenbet.h"
#include "utils/tarslog.h"
#include "context/context.h"
#include "suoha.pb.h"
#include "process/process.h"
#include "message/sendclientmessage.h"
#include "message/sendroommessage.h"
#include "logic/gamelogic/core/endtimer.h"
#include "logic/gamelogic/core/begintimer.h"
#include "logic/gamelogic/core/tokento.h"
#include "config/gameconfig.h"
#include "CommonCode.pb.h"
#include "third.pb.h"

using namespace nndef;

namespace game
{
    namespace logic
    {
        namespace clientlogic
        {
            void TokenBet(long uid, const vector<char> &vecMsgData, GameRoot *root, bool Uop, bool left, string err_msg, bool fromAI)
            {
                __TRY__

                using namespace context;
                using namespace process;
                using namespace message;
                using namespace gamelogic;
                using namespace config;
                using namespace RoomSo;

                cid_t tokencid = root->con->getTokenCid();
                User *user = root->con->getUserByUid(uid);
                if (!user || user->isMidSit() || user->getCid() != tokencid || root->pro->getProcess() > NN_STATE_FOUR_CARD || root->pro->getProcess() < NN_STATE_FIRST_CARD )
                {
                    DLOG_TRACE("roomid:" << root->roomid() << ",token bet. user state err, cid: " <<  tokencid << ", process: "<< root->pro->getProcess());
                    return;
                }

                XGameSHProto::SH_msg2csTokenBet shcm4 = pbToObj<XGameSHProto::SH_msg2csTokenBet>(vecMsgData);
                DLOG_TRACE("roomid:" << root->roomid() << ", process: "<< root->pro->getProcess() << ",token bet. shcm4: "<< logPb(shcm4));

                XGameSHProto::SH_msg2csTokenBet shcm2;
                shcm2.set_iresultid(0);
                shcm2.set_icid(user->getCid());
                shcm2.set_iact(shcm4.iact());

                long roundBetNum =  user->getRoundBetNum(root->pro->getProcess());
                long call_num = root->con->getRoundMaxBetNum() - roundBetNum;
                long min_raise_num = root->con->getRoundMaxBetNum() - roundBetNum + root->cfg->getFrontBet();
                long allin_num = user->getSHWealth() < (root->con->getUserRemainMinWealth() + call_num) ? user->getSHWealth() : (root->con->getUserRemainMinWealth() + call_num);
                E_NN_ACT act = user->getAct();

                if (!(shcm4.iact() & act) || shcm4.lbetscore() > user->getSHWealth()    ||
                    (shcm4.iact() == NN_ACT_RAISE && shcm4.lbetscore() < min_raise_num) ||
                    (shcm4.iact() == NN_ACT_FOLLOW && call_num > user->getSHWealth())   ||
                    (shcm4.iact() == NN_ACT_ALLIN &&  allin_num > user->getSHWealth()))
                {
                    DLOG_TRACE("roomid:" << root->roomid() << ", user bet err, uid: " << user->getUid() <<", roundBetNum: "<< roundBetNum
                        <<", call_num: "<< call_num << ", min_raise_num: "<< min_raise_num <<", allin_num: "<< allin_num);
                    shcm2.set_iresultid(XGameRetCode::GAME_ROOM_BET_ERR);
                    sendClientMessage<XGameSHProto::SH_msg2csTokenBet>(user->getUid(), XGameSHProto::SH_msg2csTokenBet_E, shcm2, root);
                    return;
                }

                if(shcm4.iact() == NN_ACT_ALLIN)
                {
                    user->setAllIn(true);
                    shcm2.set_lbetscore(allin_num);  
                    root->con->setRobotComParam("allAddNum", "add", 1);
                }
                else if(shcm4.iact() == NN_ACT_PASS || shcm4.iact() == NN_ACT_FOLLOW)
                {
                    shcm2.set_lbetscore(root->con->getRoundMaxBetNum() - roundBetNum);
                    //对手allin时候 此时玩家也记录成allin
                    bool other_allin = false;
                    std::map<cid_t, User> &usermap = root->con->refUserMap();
                    for (auto it = usermap.begin(); it != usermap.end(); it++)
                    {
                        if(it->second.getUid() == user->getUid())
                        {
                            continue;
                        }
                        other_allin = it->second.isAllIn();
                    }
                    user->setAllIn(other_allin);
                    if(user->isAllIn())
                    {
                       shcm2.set_iact(NN_ACT_ALLIN); 
                    } 
                }
                else if(shcm4.iact() == NN_ACT_RAISE)
                {
                    if(shcm4.lbetscore() >= allin_num)
                    {
                        shcm2.set_iact(NN_ACT_ALLIN); 
                        user->setAllIn(NN_ACT_ALLIN);
                    }
                    else
                    {
                        shcm2.set_lbetscore(shcm4.lbetscore());
                    }
                    root->con->setRobotComParam("allAddNum", "add", 1);
                    user->setRobotUserParam("isSelfAdd", "", true);
                }
                else
                {
                    user->setFold(true);
                }
                user->addRoundBetnumList(root->pro->getProcess(), shcm2.lbetscore());
                user->addRoundActionList(root->pro->getProcess(), shcm2.iact());
                user->setSHWealth(user->getSHWealth() - shcm2.lbetscore());
                user->setRobotUserParam("isSelfBet", "", shcm2.lbetscore() > 0);
                user->setDone(true);
                
                root->con->setRobotComParam("isBet", "", shcm2.lbetscore() > 0);

                shcm2.set_lcidscore(user->getSHWealth());
                sendClientMessage<XGameSHProto::SH_msg2csTokenBet>(user->getUid(), XGameSHProto::SH_msg2csTokenBet_E, shcm2, root);
                sendAllClientMessage<XGameSHProto::SH_msg2csTokenBet>(XGameSHProto::SH_msg2cTokenBetNotify_E, shcm2, root);
                
                if(root->con->getRoundMaxBetNum() < roundBetNum + shcm2.lbetscore())
                {
                    root->con->setRoundMaxBetNum(roundBetNum + shcm2.lbetscore());
                }
                
                user->setOption((E_NN_ACT)shcm2.iact());
                root->con->addTotalPoolNum(shcm2.lbetscore());

                DLOG_TRACE("roomid:" << root->roomid() << ",token bet. uid: "<< user->getUid() << ", betnum:"<< shcm2.lbetscore() << ", wealth:"<< user->getSHWealth());
                DLOG_TRACE("roomid:" << root->roomid() << ",token bet. shcm2: "<< logPb(shcm2));


                //牌局详情
                auto& gameDetails = root->con->getGameDetails();
                gameDetails.set_ltotalpool(root->con->getTotalPoolNum());
                auto stepinfo = gameDetails.add_stepinfo();
                stepinfo->set_ichairid(user->getCid());
                stepinfo->set_iaction(shcm2.iact());
                stepinfo->set_lbetnum(shcm2.lbetscore());
                stepinfo->set_lwealth(user->getSHWealth());
                stepinfo->set_iround(root->pro->getProcess() - 1);
                stepinfo->set_betraio((shcm2.lbetscore() * 1.00) / root->con->getTotalPoolNum());
                

              /*  DLOG_TRACE("roomid:" << root->roomid() <<"gameDetails:"<< logPb(gameDetails));*/

                EndTimer(NN_XTIME_GAME_BEGIN, root, false);

                cid_t nextcid = root->con->getNextCid(tokencid, root->cfg->getMaxSeatNum(), 1);
                root->con->setTokenCid(nextcid);
                 
                if(user->getOption() == NN_ACT_FOLD)
                {
                    root->pro->setProcess(NN_STATE_FOUR_CARD);
                }

                //下注通知
                TokenTo(root);

                __CATCH__
            }
        }
    }
}
