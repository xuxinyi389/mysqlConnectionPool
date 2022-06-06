#pragma once
#include<mysql.h>
#include<ctime>
#include<string>

using namespace std;
/*
ʵ�ֶ�MySQL���ݿ�Ĳ���
*/

class Connection {
public:
	//��ʼ�����ݿ�����
	Connection();
	//�ͷ����ݿ�������Դ
	~Connection();

	//�������ݿ�
	bool connect(string ip, unsigned short port, string username, string password, string dbname);
	//���²��� insert ��delete��update
	bool update(string sql);
	//��ѯ����
	MYSQL_RES* query(string sql);

	//ˢ��һ�����ӵ���ʼ�Ŀ���ʱ���
	void refreshAliveTime() { _alivetime = clock(); }
	clock_t getAliveTime()const { return clock() - _alivetime; }
private:
	MYSQL* _conn;  //��ʾ��MySQL Server ��һ������
	clock_t _alivetime; //��¼�������״̬�����ʼ���ʱ��
	
};
