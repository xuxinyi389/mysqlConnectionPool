// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�
// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�


//conlcusion:���ڵ��̣߳����ӳصĴ����ܴ�����̲���ʱ�䣬1000����¼1500���ޣ���1100���У��������ڶ��̶߳��ԣ�10000����¼��4�̡߳�
//4916ms���ޣ�,4750ms(��)�����Ʋ������ӳش���ʱ�����߳�2500��ʱ��2644ms��˫�߳�ʱ��4664ms�������߳�ʱ��4750�����߳�Ϊ4793ms��
//�ʷ��������ǣ�ֻҪ�漰����ͬ�̶߳����ӳؽ��в�����������������������ƿ�������߳�����һ����Χ��ʱ������ʱ����߳��������Ӳ����С�
//���ϣ��̳߳صĴ��ڿ��Ը������ݿ��Ч�ʣ���һ�����Լ����о��̳߳ء�
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
	clock_t begin = clock();    //���̵߳���δʹ�����ӳ�
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



