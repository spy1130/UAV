#include<iostream>
using namespace std;
#include <vector>
#include <algorithm>

//���������㷨  reverse
void myPrint(int val)
{
	cout << val << " ";
}
void test01()
{
	vector<int>v;
	v.push_back(10);
	v.push_back(30);
	v.push_back(50);
	v.push_back(20);
	v.push_back(40);

	cout << "��תǰ�� " << endl;
	for_each(v.begin(), v.end(), myPrint);
	cout << endl;

	cout << "��ת�� " << endl;
	reverse(v.begin(), v.end());
	for_each(v.begin(), v.end(), myPrint);
	cout << endl;

}

int main() {

	test01();

	system("pause");

	return 0;
}