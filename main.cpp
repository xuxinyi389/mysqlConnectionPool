// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单
// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件


//conlcusion:对于单线程，连接池的存在能大幅缩短插入时间，1000条记录1500（无），1100（有），但对于多线程而言，10000条记录开4线程。
//4916ms（无）,4750ms(有)，改善不大。连接池存在时，单线程2500条时间2644ms，双线程时候4664ms，但四线程时候4750，八线程为4793ms，
//故分析可能是：只要涉及到不同线程对连接池进行操作，加锁解锁操作是性能瓶颈，且线程数在一定范围内时，花费时间对线程数的增加不敏感。
//综上：线程池的存在可以改善数据库的效率，下一步可以继续研究线程池。
#include<iostream>
using namespace std;
# include "Connection.h"
# include "CommonConnectionPool.h"

int main()
{
	Connection conn;
	conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	/*Connection conn;
	char sql[1024] = { 0 };
	sprintf(sql, "insert into user(name, age,sex) values('%s','%d','%s')", "zhangsan", 20, "male");
	conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	conn.update(sql);*/
	//ConnectionPool* cp = ConnectionPool::getConnectionPool();
	//clock_t begin = clock();
	//for (int i = 0; i < 2500; ++i) {
	//	char sql[1024] = { 0 };
	//	sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//		"zhangsan", 20, "male");
	//	/*shared_ptr<Connection> sp = cp->getConnection();
	//	sp->update(sql);*/
	//	Connection conn;
	//	conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	//	conn.update(sql);
	//}
	//cout << (clock() - begin) << endl;
	clock_t begin = clock();    //多线程调用未使用连接池
	thread t1([&]() {
		ConnectionPool* cp = ConnectionPool::getConnectionPool();
		for (int i = 0; i < 2500; ++i) {
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
				"zhang san", 20, "male");
			/*shared_ptr<Connection> sp = cp->getConnection();
			sp->update(sql);*/
			/*Connection conn;
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");*/
			conn.update(sql);
		}
		});
	cout << (clock() - begin) << endl;

	thread t2([&]() {
		ConnectionPool* cp = ConnectionPool::getConnectionPool();
		for (int i = 0; i < 2500; ++i) {
			char sql[1024] = { 0 };
			sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
				"zhang san", 20, "male");
			/*shared_ptr<Connection> sp = cp->getConnection();
			sp->update(sql);*/
			/*Connection conn;
			conn.connect("127.0.0.1", 3306, "root", "123456", "chat");*/
			conn.update(sql);
		}
		});
	cout << (clock() - begin) << endl;
	//thread t3([]() {
	//	ConnectionPool* cp = ConnectionPool::getConnectionPool();
	//	for (int i = 0; i < 2500; ++i) {
	//		char sql[1024] = { 0 };
	//		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//			"zhang san", 20, "male");
	//		shared_ptr<Connection> sp = cp->getConnection();
	//		sp->update(sql);
	//		/*Connection conn;
	//		conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	//		conn.update(sql);*/
	//	}
	//	});
	//cout << (clock() - begin) << endl;
	//thread t4([]() {
	//	ConnectionPool* cp = ConnectionPool::getConnectionPool();
	//	for (int i = 0; i < 2500; ++i) {
	//		char sql[1024] = { 0 };
	//		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//			"zhang san", 20, "male");
	//		shared_ptr<Connection> sp = cp->getConnection();
	//		sp->update(sql);
	//		/*Connection conn;
	//		conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	//		conn.update(sql);*/
	//	}
	//	});
	//thread t5([]() {
	//	ConnectionPool* cp = ConnectionPool::getConnectionPool();
	//	for (int i = 0; i < 2500; ++i) {
	//		char sql[1024] = { 0 };
	//		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//			"zhang san", 20, "male");
	//		shared_ptr<Connection> sp = cp->getConnection();
	//		sp->update(sql);
	//		/*Connection conn;
	//		conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	//		conn.update(sql);*/
	//	}
	//	});
	//thread t6([]() {
	//	ConnectionPool* cp = ConnectionPool::getConnectionPool();
	//	for (int i = 0; i < 2500; ++i) {
	//		char sql[1024] = { 0 };
	//		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//			"zhang san", 20, "male");
	//		shared_ptr<Connection> sp = cp->getConnection();
	//		sp->update(sql);
	//		/*Connection conn;
	//		conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	//		conn.update(sql);*/
	//	}
	//	});
	//thread t7([]() {
	//	ConnectionPool* cp = ConnectionPool::getConnectionPool();
	//	for (int i = 0; i < 2500; ++i) {
	//		char sql[1024] = { 0 };
	//		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//			"zhang san", 20, "male");
	//		shared_ptr<Connection> sp = cp->getConnection();
	//		sp->update(sql);
	//		/*Connection conn;
	//		conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	//		conn.update(sql);*/
	//	}
	//	});
	//thread t8([]() {
	//	ConnectionPool* cp = ConnectionPool::getConnectionPool();
	//	for (int i = 0; i < 2500; ++i) {
	//		char sql[1024] = { 0 };
	//		sprintf(sql, "insert into user(name,age,sex) values('%s',%d,'%s')",
	//			"zhang san", 20, "male");
	//		shared_ptr<Connection> sp = cp->getConnection();
	//		sp->update(sql);
	//		/*Connection conn;
	//		conn.connect("127.0.0.1", 3306, "root", "123456", "chat");
	//		conn.update(sql);*/
	//	}
	//	});
	cout << (clock() - begin) << endl;
	t1.join();
	cout << (clock() - begin) << endl;
	t2.join();
	/*cout << (clock() - begin) << endl;
	t3.join();
	cout << (clock() - begin) << endl;
	t4.join();
	cout << (clock() - begin) << endl;*/
	/*t5.join();
	t6.join();
	t7.join();
	t8.join();*/

	clock_t end = clock();
	cout << (end - begin) << "ms" << endl;
}



