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
	//	cout << "请输入您的选择\n";
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
	//		break;//清屏
	//	}
	//} while (choice);

	Worker* worker = NULL;
	worker = new Employee(1, "张三", 1);//父类指针指向子类对象
	worker->showInfo();
	return 0;
}