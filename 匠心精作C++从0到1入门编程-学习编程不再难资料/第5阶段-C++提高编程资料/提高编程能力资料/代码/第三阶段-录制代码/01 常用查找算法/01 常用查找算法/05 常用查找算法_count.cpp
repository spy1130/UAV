//#include<iostream>
//using namespace std;
//#include <vector>
//#include <algorithm>
//#include <string>
////���ò����㷨_count
//
////1��ͳ��������������
//
//void test01()
//{
//	vector<int>v;
//
//	v.push_back(10);
//	v.push_back(40);
//	v.push_back(30);
//	v.push_back(40);
//	v.push_back(20);
//	v.push_back(40);
//
//	int num = count(v.begin(), v.end(), 40);
//
//	cout << "40��Ԫ�ظ���Ϊ�� " << num << endl;
//}
//
////2��ͳ���Զ�����������
//
//class Person
//{
//public:
//	Person(string name, int age)
//	{
//		this->m_Name = name;
//		this->m_Age = age;
//	}
//
//	bool operator==(const Person & p)
//	{
//		if (this->m_Age == p.m_Age)
//		{
//			return true;
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//	string m_Name;
//	int m_Age;
//};
//
//void test02()
//{
//	vector<Person>v;
//
//	Person p1("����", 35);
//	Person p2("����", 35);
//	Person p3("�ŷ�", 35);
//	Person p4("����", 30);
//	Person p5("�ܲ�", 40);
//
//	//����Ա���뵽������
//	v.push_back(p1);
//	v.push_back(p2);
//	v.push_back(p3);
//	v.push_back(p4);
//	v.push_back(p5);
//
//	Person p("�����", 35);
//
//	int num = count(v.begin(), v.end(), p);
//
//	cout << "�������ͬ��������Ա����Ϊ��" << num << endl;
//}
//
//int main() {
//	
//	//test01();
//
//	test02();
//
//	system("pause");
//
//	return 0;
//}