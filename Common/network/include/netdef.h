/**
* \file netdef.h
* \brief �����Ľṹ����
*
* Copyright (c) 2019
* All rights reserved.
*
* \version 1.0
* \author jj
*/

#ifndef __NET_DEFINE_H__
#define __NET_DEFINE_H__

/**
* \brief ������غ궨��
* \ingroup net_group
*/
enum
{
    TID_LEN                 = 22,       // ����ID����
    PACKAGE_HEAD_LEN        = 60,       // ��ͷ����
    PACKAGE_LEN_MAX         = (1024*8), ///< ������Ϣ�������ֵ
    PACKAGE_POOL_INIT_NUM   = 500,      ///< ������س�ʼ����
    SOCKET_POOL_INIT_NUM    = 500,      ///< �׽��ֳس�ʼ����
};
    



#endif // __NET_DEF_H__
