//#include<iostream>
//using namespace std;
//#include <vector>
//
////vector��������
//
//void printVector(vector<int>&v)
//{
//	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
//	{
//		cout << *it << " ";
//	}
//	cout << endl;
//}
//
////1������ʹ��
//void test01()
//{
//	vector<int>v1;
//	for (int i = 0; i < 10; i++)
//	{
//		v1.push_back(i);
//	}
//
//	cout << "����ǰ�� " << endl;
//	printVector(v1);
//
//	vector<int>v2;
//	for (int i = 10; i > 0; i--)
//	{
//		v2.push_back(i);
//	}
//	printVector(v2);
//
//
//	cout << "������ " << endl;
//	v1.swap(v2);
//	printVector(v1);
//	printVector(v2);
//
//}
//
////2��ʵ����;
////����swap���������ڴ�ռ�
//void test02()
//{
//	vector<int>v;
//	for (int i = 0; i < 100000; i++)
//	{
//		v.push_back(i);
//	}
//
//	cout << "v������Ϊ�� " << v.capacity() << endl;
//	cout << "v�Ĵ�СΪ�� " << v.size() << endl;
//
//
//	v.resize(3); //����ָ����С
//	cout << "v������Ϊ�� " << v.capacity() << endl;
//	cout << "v�Ĵ�СΪ�� " << v.size() << endl;
//
//	//����swap�����ڴ�
//	vector<int>(v).swap(v); 
//
//	cout << "v������Ϊ�� " << v.capacity() << endl;
//	cout << "v�Ĵ�СΪ�� " << v.size() << endl;
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