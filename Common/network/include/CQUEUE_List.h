
/**********************************************************
 * name              : CQUEUE_List.h
 * Description:      : 
 * Create by         :
 * Last Modified int : 2019-8-30
 *********************************************************/

#ifndef _CQUEUE_List_H_
#define _CQUEUE_List_H_
#include "netdef.h"
#include "time_piece.h"
#include "typedef.h"
#include <cstdlib>
#include <stdio.h>  
#include <unistd.h>  
#include <pthread.h>


#define	MAXQUEUE            (40)        // 0:���ж��� 1-10:�������� 11-n_send_threads:���Ͷ���
#define	MAXHASHLIST	        (5999)      //
//#define MAXBUFFERLENGTH     (8*1024)    //����

typedef enum
{
	QUEUE_FREE          = 0,	// ���ж���
	QUEUE_CLIENT_READ   = 1,	// �ͻ��˶����� 
	QUEUE_CLIENT_WRITE  = 2,    // �ͻ���д����
    QUEUE_SEND          = 11,	// �ͻ������ݷ��Ͷ���,���������, �� 11~(11+n_send_threads)
} QUEUE_NAME;

enum {
    PKT_TYPE_DEFAULT    = 0,
    PKT_TYPE_DISCARD    = 1,    //�ڲ�����,������Ͷ���,����ҪӦ��
    PKT_TYPE_DELAY_DONE = 2,    //��Ҫ��ʱ����ı���
}; //DEFINE_PACKET_TYPE

typedef struct listsmg
{   
    uint32  nCmd;                   //����
    uint32  nErrCode;               //������
    char    szTransID[TID_LEN];     //����ID[ģ��ID+����ID+Ψһ�Ӵ�_�����Ӵ�]
    int     cPacketType;            //����(��DEFINE_PACKET_TYPE����)
    int     connfd;                 //����fd      
    uint32  nUniqueID;              //����Ψһ���(Ϊÿ�����ӷ���һ��Ψһ���)
    uint64  nCliConnID;             //�ͻ���(����ն�)����ΨһID(api/brain���ݸ�ֵƥ��ָ���Ŀͻ���)
                                    //   1.����-Ӧ������Ϣ: ����˰�ԭ������
                                    //   2.���������֪ͨ����Ϣ:(acpcsvr)��Ҫ�ҵ������redis�Ķ�Ӧֵ
    uint32  nRoleID;                //��ɫID
    uint32  nRemoteServerID;        //���ӶԶ˵�ServerID
        
    char    sAddr[32];              //IP��ַ
    unsigned short  nPort;          //�˿�    
    CTimePiece  recv_time;          //����ʱ��
    uint32      nDelayTime;         //��ʱʱ��(��λ:����) cPacketType=PKT_TYPE_DELAY_DONE��Ч
    uint32      nDelayTimes;        //��ʱ���� cPacketType=PKT_TYPE_DELAY_DONE��Ч
    
    unsigned short len;                     //���峤��                                    
    unsigned short recv_len;                //�ѽ��ճ���
    char cPacketBuffer[PACKAGE_LEN_MAX];    //��������
    char *pRespBuffer;                      //��������ָ��(��ʱ����)
	char *cAddBuffer;                       //��������ָ��(��ʱ����)
    struct listsmg * next;                  // next node           
    struct listsmg * previous;              // previous node        

    void Reset() {
        nCmd                = 0;
        nErrCode            = 0;
        szTransID[0]        = 0;
        cPacketType         = PKT_TYPE_DEFAULT;
        connfd              = 0;
        sAddr[0]            = 0;
        nPort               = 0;
        len                 = 0;
        cPacketBuffer[0]    = 0;
        nUniqueID           = 0;
        nCliConnID          = 0;
        nRoleID             = 0;
        nRemoteServerID     = 0;
        recv_len            = 0;
        nDelayTime          = 0;
        nDelayTimes         = 0;
        
        recv_time.Restart();
    }
}LISTSMG;

typedef struct queue_data
{
    int packet_num; 
    int hash_num; 
    int queue[MAXQUEUE]; 
}QUEUE_DATA;


class CQUEUE_List
{

public:
	LISTSMG *area_head;
	LISTSMG *queue_head[MAXQUEUE];
	int     n_total_node;
	int     *n_queue_node[MAXQUEUE];
	int     n_hash_node;

public:
	LISTSMG *queue_hash[MAXHASHLIST];

private:
	pthread_mutex_t queue_hash_mutex;
	pthread_mutex_t queue_mutex[MAXQUEUE];
	pthread_cond_t  queue_cond[MAXQUEUE];
    CQUEUE_List();
    
public:
	static CQUEUE_List* Instance()
    {
        static CQUEUE_List m_instance;
        return &m_instance;
    }
    
	~CQUEUE_List();

	int CreateQueue(int MaxNumber );

	int FreeQueue( void );

	int CheckQueue( int queue_num );

	int GetQueueNum( int queue_num ,int *o_num);

	LISTSMG * GetBlockNode( int queue_num ,int *o_num);

	LISTSMG * GetNoBlockNode( int queue_num ,int *o_num);
	LISTSMG * GetNode( int queue_num ,int *o_num);

	int SetNode( LISTSMG * p,int queue_num );


	void GetQueueNum( QUEUE_DATA *in_data );

}; /* end class CQUEUE_List */

#endif	/* _CQUEUE_List_H */

