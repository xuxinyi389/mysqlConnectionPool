#pragma once
#include<string>
#include<queue>
#include<mutex>
#include<iostream>
#include<atomic> //原子类型，保证加法的线程安全
#include<thread>
#include<condition_variable>
#include<memory>
#include<functional>
using namespace std;
#include "Connection.h"
/*
实现连接池功能模块
*/
class ConnectionPool
{
public:
	// 获取连接池对象实例
	static ConnectionPool* getConnectionPool();
	//给外部提供一个接口，从连接池获取一个可用的空闲连接
	shared_ptr<Connection> getConnection();

//private:    //暂时注释便于外部调用调试
	//单例#1 构造函数私有化
	ConnectionPool();
	
	//从配置文件中加载配置项
	bool loadConfigFile();

	//运行在独立的线程中，专门负责生产新连接
	void produceConnectionTask();

	//扫描空闲时间大于maxIdleTime的空闲连接，并对超时的连接回收，杀死并释放资源
	void scannerConnectionTask();

	string _ip;  //mysql的ip地址
	unsigned short _port;  //mysql的端口号3306
	string _username;  //mysql登录用户名
	string _password;  //mysql登录密码
	string _dbname;  //连接的数据库的名称
	int _initSize;  //连接池的初始连接量
	int _maxSize;  //连接池的最大连接量
	int _maxIdleTime;  //连接池的最大空闲时间
	int _connectionTimeout;  //连接池获取连接的超时时间

	queue<Connection*> _connectionQue;  //存储mysql连接的队列(应该是线程安全的)
	mutex _queueMutex;  //维护连接队列线程安全的互斥锁
	atomic_int _connectionCnt;  //记录连接池所创建的connection总数目
	condition_variable cv;  //设置条件变量，用于连接生产线程与连接消费线程的通信
};

