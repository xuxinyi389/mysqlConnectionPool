#pragma once
#include<string>
#include<queue>
#include<mutex>
#include<iostream>
#include<atomic> //ԭ�����ͣ���֤�ӷ����̰߳�ȫ
#include<thread>
#include<condition_variable>
#include<memory>
#include<functional>
using namespace std;
#include "Connection.h"
/*
ʵ�����ӳع���ģ��
*/
class ConnectionPool
{
public:
	// ��ȡ���ӳض���ʵ��
	static ConnectionPool* getConnectionPool();
	//���ⲿ�ṩһ���ӿڣ������ӳػ�ȡһ�����õĿ�������
	shared_ptr<Connection> getConnection();

//private:    //��ʱע�ͱ����ⲿ���õ���
	//����#1 ���캯��˽�л�
	ConnectionPool();
	
	//�������ļ��м���������
	bool loadConfigFile();

	//�����ڶ������߳��У�ר�Ÿ�������������
	void produceConnectionTask();

	//ɨ�����ʱ�����maxIdleTime�Ŀ������ӣ����Գ�ʱ�����ӻ��գ�ɱ�����ͷ���Դ
	void scannerConnectionTask();

	string _ip;  //mysql��ip��ַ
	unsigned short _port;  //mysql�Ķ˿ں�3306
	string _username;  //mysql��¼�û���
	string _password;  //mysql��¼����
	string _dbname;  //���ӵ����ݿ������
	int _initSize;  //���ӳصĳ�ʼ������
	int _maxSize;  //���ӳص����������
	int _maxIdleTime;  //���ӳص�������ʱ��
	int _connectionTimeout;  //���ӳػ�ȡ���ӵĳ�ʱʱ��

	queue<Connection*> _connectionQue;  //�洢mysql���ӵĶ���(Ӧ�����̰߳�ȫ��)
	mutex _queueMutex;  //ά�����Ӷ����̰߳�ȫ�Ļ�����
	atomic_int _connectionCnt;  //��¼���ӳ���������connection����Ŀ
	condition_variable cv;  //���������������������������߳������������̵߳�ͨ��
};

