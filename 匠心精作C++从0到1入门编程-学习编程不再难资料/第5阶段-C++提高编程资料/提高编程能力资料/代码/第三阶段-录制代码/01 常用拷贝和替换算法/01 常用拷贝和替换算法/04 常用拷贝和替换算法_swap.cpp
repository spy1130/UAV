#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>

//���ÿ������滻�㷨 swap
void myPrint(int val)
{
	cout << val << " ";
}
void test01()
{
	vector<int>v1;
	vector<int>v2;

	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v2.push_back(i+100);
	}

	cout << "����ǰ�� " << endl;
	for_each(v1.begin(), v1.end(), myPrint);
	cout << endl;
	for_each(v2.begin(), v2.end(), myPrint);
	cout << endl;

	cout << "-----------------" << endl;
	cout << "������ " << endl;

	swap(v1, v2);

	for_each(v1.begin(), v1.end(), myPrint);
	cout << endl;
	for_each(v2.begin(), v2.end(), myPrint);
	cout << endl;

}

int main() {

	test01();

	system("pause");

	return 0;
}