#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>

//���ò����㷨  count_if

//ͳ��������������
class Greater20
{
public:
	bool operator()(int val)
	{
		return val > 20;
	}
};

void test01()
{
	vector<int>v;
	v.push_back(10);
	v.push_back(40);
	v.push_back(30);
	v.push_back(20);
	v.push_back(40);
	v.push_back(20);

	int num = count_if(v.begin(), v.end(), Greater20());

	cout << "����20��Ԫ�ظ���Ϊ�� " << num << endl;
}

class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}
	string m_Name;
	int m_Age;
};

class AgeGreater20
{
public:
	bool operator()(const Person & p)
	{
		return p.m_Age > 20;
	}
};

//ͳ���Զ�����������
void test02()
{
	vector<Person>v;
	
	Person p1("����", 35);
	Person p2("����", 35);
	Person p3("�ŷ�", 35);
	Person p4("����", 40);
	Person p5("�ܲ�", 20);

	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p5);

	//ͳ��  ����20����Ա����
	int num = count_if(v.begin(), v.end(), AgeGreater20());
	cout << "����20�����Ա����Ϊ��" << num << endl;
}

int main() {

	//test01();

	test02();

	system("pause");

	return 0;
}