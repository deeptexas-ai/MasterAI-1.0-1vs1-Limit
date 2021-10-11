/**
* \file net_msg.h
* \brief ������Ϣ����
*
* Copyright (c) 2019
* All rights reserved.
*
* \version 1.0
* \author jj
*/

#ifndef __NET_MSG_H__
#define __NET_MSG_H__

#include <arpa/inet.h>

#include "typedef.h"
#include "google/protobuf/message.h"
#include "netdef.h"
#include "CQUEUE_List.h"
    
#pragma pack (push,1)

extern uint64 htonl64(uint64 host64);
extern uint64 ntohl64(uint64 net64);


//��Ϣͷ��
struct NetMsgHead
{
    uint32  m_nLen;                     //����
    uint32  m_nCmd;                     //����
    uint32  m_nErrCode;                 //������
    char    m_szTransID[TID_LEN];       //����ID = ģ��ID[2λ]����ID[3λ]Ψһ�Ӵ�[10λ]-�����Ӵ�[4λ], ��20λ,���0
                                        //ģ��ID��2λ���̶�����
                                        //����ID��3λ��ÿ��ģ��������ID
                                        //Ψһ����10λ���ͻ��˵�ÿ��TCP�����һ��Ψһ��
                                        //�Ӵ����У�4λ��0001 - n��Ψһ����ͬ��TCP����������ѭ��ʹ��
    uint64  m_nCliConnID;               //�ͻ���(����ն�)����ΨһID(api���ݸ�ֵƥ��ָ���Ŀͻ���)
    char    m_sReserved[18];	        //����
    
    
    //���캯��
    NetMsgHead()
    {
        memset(this, 0, sizeof(NetMsgHead));
    }

    //���캯��
    NetMsgHead(uint32 len, uint32 cmd, uint32 errcode, uint64 nCliConnID, const char *szTransID)
    {
        m_nLen      = len;
        m_nCmd      = cmd;
        m_nErrCode  = errcode;
        m_nCliConnID= nCliConnID;
        snprintf(m_szTransID, sizeof(m_szTransID), "%s", szTransID);
        m_szTransID[TID_LEN - 1] = 0;
    }

    //����ͷ
    bool UnpackFromArray(const char * pData, size_t nLen)
    {
        if (pData == NULL || nLen < sizeof(NetMsgHead))
        {
            return false;
        }

        m_nLen      = ntohl(((NetMsgHead *)(pData))->m_nLen);
        m_nCmd      = ntohl(((NetMsgHead *)(pData))->m_nCmd);
        m_nErrCode  = ntohl(((NetMsgHead *)(pData))->m_nErrCode);
        m_nCliConnID= ntohl64(((NetMsgHead *)(pData))->m_nCliConnID);
        memcpy(m_szTransID, ((NetMsgHead *)(pData))->m_szTransID, sizeof(m_szTransID) - 1);
        m_szTransID[TID_LEN - 1] = 0;

        return true;
    }

    void head_hton() {
        m_nLen      = htonl(m_nLen);
        m_nCmd      = htonl(m_nCmd);
        m_nErrCode  = htonl(m_nErrCode);
        m_nCliConnID= htonl64(m_nCliConnID);
    }
};
#pragma pack (pop)

/**
* \brief ���������
* \param cmd ����
* \param errcode ������
* \param szTransID ����ID
* \param nRoleID ������Ϣ��roleID
* \param pbMsg pb��Ϣ
*/
extern int DoComNetPacket(LISTSMG *p, uint32 cmd, uint32 errcode, const char *szTransID, uint64 nCliConnID, const google::protobuf::Message *pbMsg, uint32 nRoleID = 0);
extern int DoComNetPacket(LISTSMG *p, const char *szTransID, int fd, uint32 nUniqueID, uint64 nCliConnID, const char *buf, uint32 nRoleID = 0);
extern int DoResponsePacket(LISTSMG *p, uint32 errcode, const google::protobuf::Message *pbMsg, uint32 nRoleID = 0);
extern int DoResponsePacket2(LISTSMG *p, uint32 errcode, const char *buf);

extern std::string ProtobufToString(const google::protobuf::Message &pbMsg);

#endif // __NET_MSG_H__
