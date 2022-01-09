#include<iostream>
using namespace std;
#include"workManager.h"
#include "work.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"

int main()
{
	workManager wm;
	int choice;
	do
	{
		wm.show_Menue();
		cout << "请输入您的选择\n";
		cin >> choice;
		switch (choice)
		{
		case 0:
			wm.exitSystem();
			break;
		case 1:
			wm.Add_Emp();
			break;
		case 2:
			wm.show_Emp();
			break;
		case 3:
			wm.del_Emp();
			break;
		case 4:
			wm.Mod_Emp();
			break;
		case 5:
			wm.Find_Emp();
			break;
		case 6:
			wm.Sort_Emp();
			break;
		case 7:
			wm.Clean_file();
			break;
		default:
			system("cls");
			break;//清屏
		}
	} while (choice);

	//Worker* worker1 = NULL;
	//worker1 = new Employee(1, "张三", 1);//父类指针指向子类对象
	//worker1->showInfo();
	//
	//Worker* worker2 = NULL;
	//worker2 = new Boss(2, "李四", 2);
	//worker2->showInfo();

	//Worker* worker3 = NULL;
	//worker3 = new Manager(3, "王五", 3);
	//worker3->showInfo();

	//delete worker1;
	//delete worker2;
	//delete worker3;

	
	return 0;
}
