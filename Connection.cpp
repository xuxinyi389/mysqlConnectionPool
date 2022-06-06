#include"public.h"
#include "Connection.h"
#include <iostream>
using namespace std;

Connection::Connection()
{
	/*
	初始化数据库连接。
	分配或初始化与mysql_real_connect()相适应的MYSQL对象。
	如果mysql是NULL指针，该函数将分配、初始化、并返回新对象。否则，将初始化对象，并返回对象的地址。
	如果mysql_init()分配了新的对象，当调用mysql_close()来关闭连接时。将释放该对象。
	*/
	_conn = mysql_init(nullptr);
}

Connection::~Connection()
{
	//释放数据库连接资源,调用mysql_close()来关闭连接时。将释放该对象。
	if(_conn != nullptr)
	{
		mysql_close(_conn);
	}
	
}


bool Connection::connect(string ip, unsigned short port,
	string username, string password, string dbname)
{
	// 连接数据库
	MYSQL* p = mysql_real_connect(_conn, ip.c_str(), username.c_str(),
		password.c_str(), dbname.c_str(), port, nullptr, 0);
	return p != nullptr;
}

bool Connection::update(string sql)
{
	//更新操作 insert、delete、update
	if (mysql_query(_conn, sql.c_str()))
	{
		LOG("更新失败" + sql);
		return false;
	}
	return true;
}







MYSQL_RES* Connection::query(string sql)
{
	// 查询操作 select
	if (mysql_query(_conn, sql.c_str()))
	{
		LOG("查询失败:" + sql);
		return nullptr;
	}
	return mysql_use_result(_conn);
}