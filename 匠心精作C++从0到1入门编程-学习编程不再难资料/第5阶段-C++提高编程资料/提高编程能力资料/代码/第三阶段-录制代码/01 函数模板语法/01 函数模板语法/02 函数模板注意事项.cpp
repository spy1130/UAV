//#include<iostream>
//using namespace std;
//
////����ģ��ע������
//
//template<class T> //typename�����滻��class
//void mySwap(T&a, T&b)
//{
//	T temp = a;
//	a = b;
//	b = temp;
//}
//
////1���Զ������Ƶ��������Ƶ���һ�µ���������T�ſ���ʹ��
//void test01()
//{
//	int a = 10;
//	int b = 20;
//	char c = 'c';
//	//mySwap(a, b); //��ȷ��
//	//mySwap(a, c); //�����Ƶ�����һ�µ�T����
//	cout << "a = " << a << endl;
//	cout << "b = " << b << endl;
//}
//
////2��ģ�����Ҫȷ����T���������ͣ��ſ���ʹ��
//template<class T>
//void func()
//{
//	cout << "func ����" << endl;
//}
//
//void test02()
//{
//	func<int>();
//}
//
//int main() {
//
//	//test01();
//	test02();
//
//	system("pause");
//
//	return 0;
//}