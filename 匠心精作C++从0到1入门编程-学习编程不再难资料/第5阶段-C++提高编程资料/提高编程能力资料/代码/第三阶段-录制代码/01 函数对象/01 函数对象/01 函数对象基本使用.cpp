//#include<iostream>
//using namespace std;
//#include <string>
//
////�������� ���º�����
///*
//- ����������ʹ��ʱ����������ͨ������������, �����в����������з���ֵ
//- �������󳬳���ͨ�����ĸ����������������Լ���״̬
//- �������������Ϊ��������
//*/
//
//class MyAdd
//{
//public:
//	int operator()(int v1,int v2)
//	{
//		return v1 + v2;
//	}
//
//};
//
//// 1������������ʹ��ʱ����������ͨ������������, �����в����������з���ֵ
//void test01()
//{
//	MyAdd myAdd;
//	cout <<  myAdd(10, 10) <<endl;
//}
//
//
////2���������󳬳���ͨ�����ĸ����������������Լ���״̬
//class MyPrint
//{
//public:
//	MyPrint()
//	{
//		this->count = 0;
//	}
//	void operator()(string test)
//	{
//		cout << test << endl;
//		this->count++;
//	}
//
//	int count; // �ڲ��Լ�״̬
//};
//
//void test02()
//{
//	MyPrint myPrint;
//	myPrint("hello world");
//	myPrint("hello world");
//	myPrint("hello world");
//	myPrint("hello world");
//
//	cout << "myPrint���ô���Ϊ�� " << myPrint.count << endl;
//}
//
////3���������������Ϊ��������
//void doPrint(MyPrint & mp, string test)
//{
//	mp(test);
//}
//
//void test03()
//{
//	MyPrint myPrint;
//	doPrint(myPrint, "Hello c++");
//}
//
//int main() {
//
//	//test01();
//
//	//test02();
//
//	test03();
//
//	system("pause");
//
//	return 0;
//}