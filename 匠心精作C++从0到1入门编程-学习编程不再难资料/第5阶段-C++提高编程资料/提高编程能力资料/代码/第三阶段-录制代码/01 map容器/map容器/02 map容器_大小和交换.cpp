//#include<iostream>
//using namespace std;
//#include <map>
////map���� ��С�ͽ���
//
////��С
//void test01()
//{
//	map<int, int>m;
//	m.insert(pair<int, int>(1, 10));
//	m.insert(pair<int, int>(2, 20));
//	m.insert(pair<int, int>(3, 30));
//
//	if (m.empty())
//	{
//		cout << "mΪ��" << endl;
//	}
//	else
//	{
//		cout << "m��Ϊ��" << endl;
//		cout << "m�Ĵ�СΪ�� " << m.size() << endl;
//	}
//}
//
//void printMap(map<int, int>&m)
//{
//	for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
//	{
//		cout << "key = " << it->first << " value = " << it->second << endl;
//	}
//	cout << endl;
//}
//
////����
//void test02()
//{
//	map<int, int>m;
//	m.insert(pair<int, int>(1, 10));
//	m.insert(pair<int, int>(2, 20));
//	m.insert(pair<int, int>(3, 30));
//
//	map<int, int>m2;
//	m2.insert(pair<int, int>(4, 100));
//	m2.insert(pair<int, int>(5, 200));
//	m2.insert(pair<int, int>(6, 300));
//
//	cout << "����ǰ�� " << endl;
//	printMap(m);
//	printMap(m2);
//
//	m.swap(m2);
//	cout << "������ " << endl;
//	printMap(m);
//	printMap(m2);
//
//}
//
//int main() {
//
//	//test01();
//	test02();
//	system("pause");
//
//	return 0;
//}