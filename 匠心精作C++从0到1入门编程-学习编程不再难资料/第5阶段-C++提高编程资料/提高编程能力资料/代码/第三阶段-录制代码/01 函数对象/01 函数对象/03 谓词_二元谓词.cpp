//#include<iostream>
//using namespace std;
//#include <vector>
//#include <algorithm>
//
////��Ԫν��
//class MyCompare
//{
//public:
//	bool operator()(int va11,int val2)
//	{
//		return va11 > val2;
//	}
//
//};
//
//void test01()
//{
//	vector<int>v;
//	v.push_back(10);
//	v.push_back(40);
//	v.push_back(20);
//	v.push_back(30);
//	v.push_back(50);
//
//	sort(v.begin(), v.end());
//	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
//	{
//		cout << *it << " ";
//	}
//	cout << endl;
//
//	//ʹ�ú�������  �ı��㷨���ԣ���Ϊ�������Ϊ�Ӵ�С 
//	sort(v.begin(), v.end(), MyCompare());
//
//	cout << "-----------------------" << endl;
//	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
//	{
//		cout << *it << " ";
//	}
//	cout << endl;
//
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