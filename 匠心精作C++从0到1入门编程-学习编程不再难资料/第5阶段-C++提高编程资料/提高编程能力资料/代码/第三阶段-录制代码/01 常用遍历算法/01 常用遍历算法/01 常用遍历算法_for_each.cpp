//#include<iostream>
//using namespace std;
//#include<vector>
//#include<algorithm>
//
////���ñ����㷨 for_each
//
////��ͨ����
//void print01(int val)
//{
//	cout << val << " ";
//}
//
////�º���
//class print02
//{
//public:
//	void operator()(int val)
//	{
//		cout << val << " ";
//	}
//
//};
//
//void test01()
//{
//	vector<int>v;
//	for (int i = 0; i < 10; i++)
//	{
//		v.push_back(i);
//	}
//
//	for_each(v.begin(), v.end(), print01);
//	cout << endl;
//
//	for_each(v.begin(), v.end(), print02());
//	cout << endl;
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