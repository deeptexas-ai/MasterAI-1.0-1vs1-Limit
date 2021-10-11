
/*! @file 
@brief ��־��ͷ�ļ�

�ṩ������־�Ļ������ܣ������������ļ��л��Ͳ�����־�淶���ݡ�

*/

#ifndef __SH_LOG__
#define __SH_LOG__


/*! \def LOG
\brief д��־�ĺ꣬�򻯱���

��������������shstd::log::Log�� ����ά����������־ͷ����Ҫ����id��DEBUG��־����������
LOG(LT_DEBUG, "SEND_MAIL| ip=%s| port=%u|", param1, param2);
д������id��INFO��־����������
LOG(LT_INFO_TRANS, szTransId, "SEND_MAIL| mid=%s|", param2);

//����չ����,��ʱ֧��ֵΪ0��1����Ϊ1ʱ��֧����־����д�����ļ�
LOG(LT_DEBUG, 1, "SEND_MAIL| ip=%s| port=%u|", param1, param2);
LOG(LT_INFO_TRANS, szTransId, 1, "SEND_MAIL| mid=%s|", param2);

*/
#define LOG  shstd::log::Log

//no deal time, no trans id
#define LT_DEBUG shstd::log::LOG_TYPE_DEBUG,__FILE__,__LINE__,-1,NULL
#define LT_INFO  shstd::log::LOG_TYPE_INFO,__FILE__,__LINE__,-1,NULL
#define LT_WARN  shstd::log::LOG_TYPE_WARN,__FILE__,__LINE__,-1,NULL
#define LT_ERROR shstd::log::LOG_TYPE_ERROR,__FILE__,__LINE__,-1,NULL

//no deal time, have trans id
#define LT_DEBUG_TRANS shstd::log::LOG_TYPE_DEBUG,__FILE__,__LINE__,-1
#define LT_INFO_TRANS  shstd::log::LOG_TYPE_INFO,__FILE__,__LINE__,-1
#define LT_WARN_TRANS  shstd::log::LOG_TYPE_WARN,__FILE__,__LINE__,-1
#define LT_ERROR_TRANS shstd::log::LOG_TYPE_ERROR,__FILE__,__LINE__,-1

//have deal time, have trans id
#define LT_DEBUG_ALL shstd::log::LOG_TYPE_DEBUG,__FILE__,__LINE__
#define LT_INFO_ALL  shstd::log::LOG_TYPE_INFO,__FILE__,__LINE__
#define LT_WARN_ALL  shstd::log::LOG_TYPE_WARN,__FILE__,__LINE__
#define LT_ERROR_ALL shstd::log::LOG_TYPE_ERROR,__FILE__,__LINE__

/**
* shstd��
*/
namespace shstd
{
    /*! 
    @brief shstd��֮��־��
    */
    namespace log
    {
        static const int LOG_TYPE_NULL = 0;
        static const int LOG_TYPE_DEBUG = 1;
        static const int LOG_TYPE_INFO = 2;
        static const int LOG_TYPE_WARN = 4;
        static const int LOG_TYPE_ERROR = 8;
        static const int LOG_TYPE_PRINT = 1024;


        /*! @fn int Init(const char *pszDir, const char *szModuleName, const char *szLogTypes);
        @brief ����־����г�ʼ��, ֻ�ܵ���һ��
        @param [in] pszDir ��־���·��
        @param [in] szModuleName ��־ģ�������
        @param [in] szLogTypes ��־ģ���������ͣ�debug��info��warn��error����ϴ���
		@param [in] szOwner ���ɵ���־�ļ�������
		@param [in] nExtType ��չ���ͣ����������0�����дһ����־�ļ�, ��ʱ��ֵֻ��Ϊ0��1, Ĭ��Ϊ0
        @return �ɹ�����0,ʧ�ܷ�������ֵ
        */
        int Init(const char *pszDir, const char *szModuleName, const char *szLogTypes, const char *szOwner);
        int Init(const char *pszDir, const char *szModuleName, const char *szLogTypes, unsigned int nExtType, const char *szOwner);

		/*! @fn int IsOpen();
		@brief �����־���Ƿ��Ѿ��ɹ���ʼ��
        @return �ɹ�����0:��ʶ��־��ʼ���ɹ�, ������ʾ��ʼ��ʧ�ܻ�û�г�ʼ��
        */
		int IsOpen();


		/*! @fn bool SetAsynMode(unsigned int nAsynFlushLogCnt, unsigned int nAsynFlushSeconds)
        @brief ���ϱ���־������첽ģʽ,�ڹ������̵��ò��ܳɹ�����ʼ���ɹ�����ô˽ӿڡ��ڻ�������־������£�������ֻҪ�ﵽ�κ�һ������������д�ļ���
		�ڵ��ô˽ӿ�֮ǰû�е���SvrStdInit����鿴����shstd::fun::SetMonitorParentPid��
		����첽ģʽ֮�󣬽��������л���ͬ��ģʽ���ӿ��ظ����ã���������Ч��
		@param [in] nAsynFlushLogCnt ����־�����������ﵽ��ֵ������д�ļ�������Ĭ��ֵΪ100�� ��Χ1��10000, ������Χ�ᱻ����ΪĬ��ֵ
        @param [in] nAsynFlushSeconds ˢ�ļ����ڣ���λ��,Ĭ��ÿ������дһ���ļ������л�����־������¡�Ĭ��ֵΪ1����Χ1��120��������Χ�ᱻ����ΪĬ��ֵ
        @return �����Ƿ����첽ģʽ��trueΪ�첽ģʽ��falseΪͬ��ģʽ��
        */
		bool SetAsynMode(unsigned int nAsynFlushLogCnt = 100, unsigned int nAsynFlushSeconds = 1);  

		/*! @fn bool GetAsynOption(unsigned int * pnAsynFlushLogCnt, unsigned int * pnAsynFlushSeconds);
        @brief ȡ���첽��������Ϊͬ��ģʽʱ����������ʧ��
        @param [in] pnAsynFlushLogCnt ����flush����ֵ
		@param [in] pnAsynFlushSeconds ����flushʱ��ֵ����λ��)
        @return �ɹ�����true��ʧ�ܷ���false
        */
		bool GetAsynOption(unsigned int * pnAsynFlushLogCnt, unsigned int * pnAsynFlushSeconds);


		/*! @fn void SetSyncFlushOption(unsigned int nSyncFlushLogCnt, unsigned int nSyncFlushSecond)
        @brief ����ͬ��ģʽ�µ�ˢ��������ˢ������, ����������������һ������flush
        @param [in] nSyncFlushLogCnt δˢ�����ﵽ����������ᵼ��flush��־�������ݵ��ļ���0��1��ÿ�ζ�flush, Ĭ��Ϊ1
		@param [in] nSyncFlushSecond δˢ��ʱ��ﵽ����������ᵼ��flush��־�������ݵ��ļ���Ĭ��Ϊ3600
        @return �ɹ�����true��ʧ�ܷ���false
        */
		bool SetSyncFlushOption(unsigned int nSyncFlushLogCnt=1, unsigned int nSyncFlushSecond = 3600);

		/*! @fn bool GetSyncFlushOption(unsigned int *pnSyncFlushLogCnt, unsigned int *pnSyncFlushSecond)
        @brief ȡ��ͬ��flush������������첽ģʽ���˺�����ʧ��.
        @param [in] pnSyncFlushLogCnt ����flush����ֵ
		@param [in] pnSyncFlushSecond ����flushʱ��ֵ(��λ��)
        @return �ɹ�����true��ʧ�ܷ���false
        */
		bool GetSyncFlushOption(unsigned int *pnSyncFlushLogCnt, unsigned int *pnSyncFlushSecond);


        /*! @fn void Log(int nLogType, const char *szFileName, int nLineNum, int nMilliSecs,const char *szTransId, const char *fmt, ...);
        @brief д��־
        @param [in] nLogType ��־����
        @param [in] szFileName Դ�ļ���
        @param [in] nLineNum Դ�ļ��к�
        @param [in] nMilliSecs ����ʱ��
        @param [in] szTransId ����id
        @param [in] fmt ��ʽ����
        */
        void Log(int nLogType, const char *szFileName, int nLineNum, int nMilliSecs,const char *szTransId, const char *fmt, ...);

		/*! @fn void Log(int nLogType, const char *szFileName, int nLineNum, int nMilliSecs,const char *szTransId, unsigned int nExtType, const char *fmt, ...);
        @brief ���ض�����д��־
        @param [in] nLogType ��־����
        @param [in] szFileName Դ�ļ���
        @param [in] nLineNum Դ�ļ��к�
        @param [in] nMilliSecs ����ʱ��
        @param [in] szTransId ����id
        @param [in] nExtType ��չ���ͣ����������Ϊ0�����дһ����־�ļ�, ��ʱ��ֵֻ��Ϊ0��1
        @param [in] fmt ��ʽ����
        */
        void Log(int nLogType, const char *szFileName, int nLineNum, int nMilliSecs,const char *szTransId, unsigned int nExtType, const char *fmt, ...);
		
        /******************************************************\
        * �� �� ����SetLogType
        * �������ܣ��ı���־�������
        * ��    ����[in] szLogTypes :��־ģ����������, Ϊdebug,info,warn,error�ĸ����ʵ��������
        * �� �� ֵ����
        * ��   ע ��
        \********************************************************/ 

        /*! @fn void SetLogType(const char *szLogTypes)
        @brief �ı���־�������
        @param [in] szLogTypes :��־ģ����������, Ϊdebug,info,warn,error�ĸ����ʵ��������
        */
        void SetLogType(const char *szLogTypes);  

        /*! @fn const char * GetLogType()
        @brief ȡ�õ�ǰ��־�������
        @return ��ǰ��־���������
        */
        const char * GetLogType();

        /******************************************************\
        * �� �� ����SetLogMaxSize
        * �������ܣ�������־�ļ�������С
        * ��    ����[in] nMaxSize :��־�ļ�����С
        * �� �� ֵ������ʵ�ʴ�С
        * ��   ע ��Ĭ��2G-100M
        \********************************************************/ 

        /*! @fn unsigned long SetLogMaxSize(unsigned long nMaxSize = (2 * 1024 - 100) * 1024 * 1024L); 
        @brief ������־�ļ�������С
        @param [in] nMaxSize ��־�ļ�����С������С������10G
        @return ����ʵ�ʴ�С
        */
        unsigned long SetLogMaxSize(unsigned long nMaxSize = (2 * 1024 - 100) * 1024 * 1024L); 

        
    }
}

#endif



#ifdef __DEBUG__

#define DEBUG_LOG(x) do \
{ \
	LOG x; \
} while(0); 

#else

#define DEBUG_LOG(x) ;

#endif




