//#include<iostream>
//using namespace std;
//#include <list>
//
////list���������ɾ��
//
///*
//- push_back(elem);//������β������һ��Ԫ��
//- pop_back();//ɾ�����������һ��Ԫ��
//- push_front(elem);//��������ͷ����һ��Ԫ��
//- pop_front();//��������ͷ�Ƴ���һ��Ԫ��
//- insert(pos,elem);//��posλ�ò�elemԪ�صĿ��������������ݵ�λ�á�
//- insert(pos,n,elem);//��posλ�ò���n��elem���ݣ��޷���ֵ��
//- insert(pos,beg,end);//��posλ�ò���[beg,end)��������ݣ��޷���ֵ��
//- clear();//�Ƴ���������������
//- erase(beg,end);//ɾ��[beg,end)��������ݣ�������һ�����ݵ�λ�á�
//- erase(pos);//ɾ��posλ�õ����ݣ�������һ�����ݵ�λ�á�
//- remove(elem);//ɾ��������������elemֵƥ���Ԫ�ء�
//*/
//
//void printList( const list<int>&L)
//{
//	for (list<int>::const_iterator it = L.begin(); it != L.end(); it++)
//	{
//		cout << *it << " ";
//	}
//	cout << endl;
//}
//
//void test01()
//{
//	list<int>L;
//
//	//β��
//	L.push_back(10);
//	L.push_back(20);
//	L.push_back(30);
//
//	//ͷ��
//	L.push_front(100);
//	L.push_front(200);
//	L.push_front(300);
//
//	// 300 200 100 10 20 30 
//	printList(L);
//
//	//βɾ
//	L.pop_back();
//	// 300 200 100 10 20 
//	printList(L);
//
//	//ͷɾ
//	L.pop_front();
//	// 200 100 10 20 
//	printList(L);
//
//	//insert����
//	list<int>::iterator it = L.begin();
//	L.insert(++it, 1000);
//	//  200 1000 100 10 20 
//	printList(L);
//
//	//ɾ��
//	it = L.begin();
//	L.erase(++it);
//	// 200 100 10 20 
//	printList(L);
//
//	//�Ƴ�
//	L.push_back(10000);
//	L.push_back(10000);
//	L.push_back(10000);
//	L.push_back(10000);
//	printList(L);
//
//	L.remove(10000);
//	printList(L);
//
//	//���
//	L.clear();
//	printList(L);
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