
/*! @file 
@brief һ�㺯����ͷ�ļ�

�ṩһЩ���ú������ܣ�����ϵͳ������ֹͣ�淶��
   
*/


#ifndef __SH_STD_FUN__
#define __SH_STD_FUN__
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <stdarg.h>
#include <string.h>



#pragma pack(push,1)

/**
* shstd��
*/
namespace shstd
{
    /*!
    @brief shstd��֮���ߺ�����
    */
    namespace fun
    {    
        /*! @fn char * cp2ap(char *path)
        @brief �����·��������·����ת��
        @param [in] path ���·��
        @return ���ؾ���·����ʧ�ܷ���NULL
        */
        char * cp2ap(char *path); //���·��������·��


        //�����Լ��, ����������С���nSleepSeconds
        void MonitorSelf(unsigned int nSleepSeconds = 3); //����Լ�
		void MonitorSelf(int argc, const char **argv, unsigned int nSleepSeconds = 3); //����Լ�


        /*! @fn bool KillTree(pid_t pid, unsigned int nMaxWaitSeconds = 60)
        @brief ɱ������������������Ľڵ㷢SIGINT�� Ȼ��ȴ����̵��˳������ȴ�nMaxWaitSeconds, ����û�˳��Ľ��̷���SIGKILL
        @param [in] pid ����pid
        @param [in]  nMaxWaitSeconds �ȴ��Ƴ�����
		@return �������еĽ��̶��������ˣ��ɹ�����true��ʧ�ܷ���false
        */
        bool KillTree(pid_t pid, unsigned int nMaxWaitSeconds = 45);

        //�л��û�

        /*! @fn bool ChangeRunUser(const char *szUser)
        @brief �л������û����
        @param [in] szUser Ŀ���л��û�
        @return �ɹ�����true��ʧ�ܷ���false
        */
        bool ChangeRunUser(const char *szUser);

        //argc�� argvΪmain������͸���� szModuleNameΪģ����(����lda,ms,mi ����svr��׺��), szUser���������pid·����Ӧ���û�, nochdir �Ƿ�ı�Ŀ¼��/, noclose �Ƿ񽫱�׼�������ӳ�䵽/dev/null
        /*! @fn bool SvrStdInit(int argc, const char **argv, const char *szModuleName, const char *szUser, int nochdir = 1, int noclose = 0);
        @brief �Է�����й淶�ĳ�ʼ������������ֹͣ�淶��pid�ļ��� --stop��ʱ�򣬻ᷢ��SIGINT�źŸ����̣�֪ͨҪ׼���˳����̣�Ĭ����ȴ�20�룬Ҫ�ǽ��̻�û�˳�������SIGKILL�źŵ����̡�
        @param [in] argc ���������Ĳ�����͸��ֵ
        @param [in] argv ���������Ĳ�����͸��ֵ���������а��� --debugʱ�� ���������κζ���������true���Ա���е����̵���
        @param [in] szModuleName ģ����(����lda,ms,mi ����svr��׺��)
        @param [in] szUser �������pid·����Ӧ���û�
        @param [in] nochdir �Ƿ�ı�Ŀ¼��/, 1:���л� 0���л�
        @param [in] noclose �Ƿ񽫱�׼�������ӳ�䵽/dev/null 1�����л��� 0���л�
        @return �ɹ�����true��ʧ�ܷ���false
        */
        bool SvrStdInit(int argc, const char **argv, const char *szModuleName, const char *szUser, int nochdir = 1, int noclose = 0);

		/*! @fn const char * GetWorkHomePath(bool bPrintErr = true);
        @brief ȡ�ù����ĸ�Ŀ¼�������̿�ִ�г������һ��Ŀ¼��β������'/'
        @param [in] bPrintErr, ������ʱ���Ƿ��ӡ������ʾ
        @return ���û���淶���𣬻᷵��NULL�� ���򷵻���ȷ��·����
        */
		const char * GetWorkHomePath(bool bPrintErr = true);


		/*! @fn const char * GetRunUser();
        @brief ȡ������ϵͳ���û���
        @param [in] ��
        @return ʧ�ܷ���NULL, �ɹ�����ϵͳ���ڵ��û���
        */
		const char * GetRunUser();


		/*! 
        \brief �ýṹ�����������������ip
        */
		struct IP_INFO
		{
			char ip[64];
			IP_INFO()
			{
				memset(this, 0, sizeof(IP_INFO));
			}
		};

        /*! @fn int ParseDns(const char * szDns, IP_INFO  ipinfos[], unsigned int nIpInfoSize, unsigned short port = 0);
        @brief ����dns���õ�������Ӧ��ip�����ܻ��ж��ip�����ͬʱ����ipv4��ipv6��ipv4�ڷ��������ǰ��
        @param [in] szDns ��Ҫ����������
		@param [in] ipinfos ���ص�ip��Ϣ����Ļ���
		@param [in] nIpInfoSize ���뻺���IP_INFO�ṹ����Ԫ�ص�����
		@param [in] port �������ӵĶ˿�,�����Ϊ0�����ʾ��Ҫ���Ըö˿ڵ���ͨ�ԣ����ܻ������������һ��ʱ�䣬���ؽ��Ϊ������ͨ��
        @return ʧ�ܷ��ظ�ֵ���ɹ�����������Ӧ��ip��䵽�����е����������õ���ip������nIpInfoSize��ʱ������ᱻ����
        */
		int ParseDns(const char * szDns, IP_INFO  ipinfos[], unsigned int nIpInfoSize, unsigned short port = 0);


		bool IsIpV4(const char * ip); //�Ƿ���ipv4
		bool IsIpV6(const char * ip); //�Ƿ���ipv6


		const char * GetModuleName();


        //ȡ�ù����ӽ��̱���������������ڷ������Ľ��̣����Կ���coredump�Ĵ���
        unsigned int GetForkCnt();
        time_t GetParentProgressStartup(); //����������ʱ��
        time_t GetWorkProgressStartup(); //�ӽ�������ʱ��
		pid_t GetMonitorParentPid(); //ȡ�ü�ؽ���pid


		/*! @fn bool SetMonitorParentPid(pid_t ppid); 
        @brief ���ü�ظ����̵Ľ���id,ֻ������һ�Σ�ʹ��SvrStdInit�����ķ���������ô˽ӿڣ�û��ʹ��SvrStdInit�ӿڵķ�����̲����ô˽ӿڲ��ܳɹ�������־�첽ģʽ��
        @param [in] ppid ��ظ����̵�pid
        @return �ɹ�״̬��trueΪ�ɹ���falseΪʧ��
        */
		bool SetMonitorParentPid(pid_t ppid); 


        /*! @fn char * TrimUsername(char *szUser);
        @brief ���û�����������ȥ��ǰ��ո��˫���š�������
        @param [in] szUser ��Ҫ������û���
        @return szUser�ĵ�ַ
        */
        char * TrimUsername(char *szUser);

		char * TrimMobile(char *szMobile);
       

		/*! @fn const char * DecodeDBPass(char *szEnPass, char * szDePass, int key=19); 
        @brief �����ݿ���ܺ��������н��ܣ����ܺ�Ľ�������ԭʼ�ַ���
        @param [in] szEnPass ���ܺ������
		@param [in] szDePass ���ܺ�����룬�䳤�Ȳ���С��szEnPass��2/3
		@param [in] key ���ܵĿ��ԣ�Ĭ��Ϊ19���ӽ���Ҫһ��
        @return ʧ�ܷ���NULL�� �ɹ����ؽ��ܺ������
        */
		const char * DecodeDBPass(char *szEnPass, char * szDePass, int key=19); 

		//url �����
		std::string URLencode(const std::string & strSrc);
		std::string URLdecode(const std::string & strSrc);

		//base64�����
		int Base64Dec(unsigned char *buf,const unsigned char*text,int size);
		int Base64Enc(unsigned char *buf,const unsigned char*text,int size); 


		//�ַ������
        void replace_all(std::string &str, const std::string &old_value, const std::string &new_value);

        //��ȡ��ǰ����
        std::string CurrentDate();

        /*���ַ�����ȡָ��keyֵ������
        *    ������delimiter�ָ�
        *    ��ʽ��key1=value1 key2=value2 ...
        */
        std::string GetValueBykey(const char *szBuf, const char *key, const char* delimiter);

    }
}


#pragma pack(pop)

#endif


