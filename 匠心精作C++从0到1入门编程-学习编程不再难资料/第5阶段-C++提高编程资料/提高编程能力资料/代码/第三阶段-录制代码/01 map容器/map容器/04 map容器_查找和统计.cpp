//#include<iostream>
//using namespace std;
//#include <map>
//
////map���� ���Һ�ͳ��
//void test01()
//{
//	//����
//	map<int, int>m;
//	m.insert(pair<int, int>(1, 10));
//	m.insert(pair<int, int>(2, 20));
//	m.insert(pair<int, int>(3, 30));
//	m.insert(pair<int, int>(3, 40));
//
//	map<int,int>::iterator pos = m.find(3);
//
//	if (pos != m.end())
//	{
//		cout << "�鵽��Ԫ�� key = " << (*pos).first << " value = " << pos->second << endl;
//	}
//	else
//	{
//		cout << "δ�ҵ�Ԫ��" << endl;
//	}
//
//	//ͳ��
//	//map����������ظ�key Ԫ�� ��countͳ�ƶ��� ���Ҫô��0 Ҫô��1
//	//multimap��countͳ�ƿ��ܴ���1
//	int num = m.count(3);
//	cout << "num = " << num << endl;
//}
//
//int main() {
//
//	test01();
//
//	system("pause");
//
//	return 0;
//}