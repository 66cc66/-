#include<iostream>
using namespace std;
#include"workManager.h"
#include "work.h"
#include "employee.h"
int main()
{
	//workManager wm;
	//int choice;
	//do
	//{
	//	wm.show_Menue();
	//	cout << "����������ѡ��\n";
	//	cin >> choice;
	//	switch (choice)
	//	{
	//	case 0:
	//		wm.exitSystem();
	//		break;
	//	case 1:
	//		break;
	//	case 2:
	//		break;
	//	case 3:
	//		break;
	//	case 4:
	//		break;
	//	case 5:
	//		break;
	//	case 6:
	//		break;
	//	case 7:
	//		break;
	//	default:
	//		system("cls");
	//		break;//����
	//	}
	//} while (choice);

	Worker* worker = NULL;
	worker = new Employee(1, "����", 1);//����ָ��ָ���������
	worker->showInfo();
	return 0;
}