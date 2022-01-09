#include "workManager.h"

workManager::workManager()
{
	//1，文件不存在

	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件

	//文件不存在的情况
	if (!ifs.is_open())
	{
		//cout << "文件不存在\n";//测试输出	
		this->m_EmpNum = 0;//初始化人数
		this->m_EmpArr = NULL;//初始化数组
		this->m_FileIsEmpty = true;//初始化文件为空标志
		ifs.close();
		return;
	}
	
	//2.文件存在，并且没有记录,数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空\n";
		this->m_EmpNum = 0;
		this->m_EmpArr = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3.记录着数据的
	int num = this->get_EmpNum();
	//cout << "职工人数为：" << num << endl;	
	this->m_EmpNum = num;

	//根据职工数创建数组
	this->m_EmpArr = new Worker * [this->m_EmpNum];
	//初始化职工
	this->init_Emp();

	//测试代码
	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "职工号：" << this->m_EmpArr[i]->m_Id
			<< "\t姓名：" << this->m_EmpArr[i]->m_Name
			<< "\t部门编号" << this->m_EmpArr[i]->m_DeptId << endl;
	}*/
}

workManager::~workManager()
{
	if (this->m_EmpArr != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArr != NULL)
				delete this->m_EmpArr[i];
		}
		delete[] this->m_EmpArr;
		this->m_EmpArr = NULL;
	}
}

void workManager::show_Menue()
{
	cout << " ******************************* "<< endl;
	cout << " *****欢迎使用职工管理系统!***** "<< endl;
	cout << " *********1.增加职工信息******** "<< endl;
	cout << " *********2.显示职工信息******** "<< endl;
	cout << " *********3.删除离职职工******** "<< endl;
	cout << " *********4.修改职工信息******** "<< endl;
	cout << " *********5.查找职工信息******** "<< endl;
	cout << " *********6.按照编号排序******** "<< endl;
	cout << " *********7.清空所有文档******** "<< endl;
	cout << " *********0.退出管理程序******** "<< endl;
	cout << " ******************************* "<< endl;
	cout << endl;
}

void workManager::exitSystem()
{
	cout << "欢迎下次继续使用\n";
	system("pause");
	exit(0);
}

void workManager::Ensure_consist(int Id)
{
	bool flag = false;
	while (!flag)
	{
		for (int t = 0; t < this->get_EmpNum(); t++)
		{
			if (Id == this->m_EmpArr[t]->m_Id)
			{
				flag = true;
				break;
			}
		}
		if (flag)
		{
			cout << "所输编号已存在，请输入其他编号\n";
			cin >> Id;
			flag = false;
		}
		else
			break;
	}
}

void workManager::Add_Emp()
{
	int sum = 0;
	cout << "输入所录入员工数量\n";
	cin >> sum;
	if (sum > 0)
	{
		//计算新空间大小
		int newSize = this->m_EmpNum + sum;

		//开辟新空间
		Worker** newSpace = new Worker* [newSize];

		//将原空间下的内容存放到新空间下
		if (this->m_EmpArr != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArr[i];
			}
		}

		//输入数据
		for (int i = 0; i < sum; i++)
		{
			int Id;
			string name;
			int dSelect;

			cout << "请输入第" << i + 1 << "个新职工编号：\n";
			cin >> Id;
			
			//保证Id的唯一性
			Ensure_consist(Id);

			cout << "请输入第" << i + 1 << "个新职工的姓名：\n";
			cin >> name;

			cout << "请选择该职工的职位：\n";
			cout << "1.普通职工\n";
			cout << "2.经理\n";
			cout << "3.老板\n";
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:worker = new Employee(Id, name, 1);
				break;
			case 2:worker = new Manager(Id, name, 2);
				break;
			case 3:worker = new Boss(Id, name, 3);
				break;
			default:
				break;
			}
			//将创建的职工保存到数组
			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原空间
		delete[] this->m_EmpArr;

		//更改新空间的指向
		this->m_EmpArr = newSpace;

		//更新新的个数
		this->m_EmpNum = newSize;

		//更新职工不为空的情况
		this->m_FileIsEmpty = false;

		//提示信息
		cout << "成功添加" << sum << "名职工！\n";
		this->save();
	}
	else
		cout << "输入有误\n";
	system("pause");
	system("cls");
}

//保存文件
void workManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//写文件

	//将每个数据写入到文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArr[i]->m_Id << " "
			<< this->m_EmpArr[i]->m_Name << " "
			<< this->m_EmpArr[i]->m_DeptId << endl;
	}

	ofs.close(); 
}

int workManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件

	int Id;
	int Did;
	string Name;

	int num = 0;

	while (ifs >> Id && ifs >> Name && ifs >> Did)
	{
		//记录认数
		num++;
	}
	ifs.close();

	return num;
}

void workManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int Id;
	int Did;
	string Name;

	int index = 0;

	while (ifs >> Id && ifs >> Name && ifs >> Did)
	{
		Worker* worker = NULL;

		//根据不同的部门Id创建不同对象
		if (Did == 1)
			worker = new Employee(Id, Name, Did);
		else if (Did == 2)
			worker = new Manager(Id, Name, Did);
		else
			worker = new Boss(Id, Name, Did);

		//存放在数组中
		this->m_EmpArr[index++] = worker;
	}
}

void workManager::show_Emp()
{
	if (this->m_FileIsEmpty)
		cout << "文件不存在或为空！\n";
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//利用多态调用接口
			this->m_EmpArr[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

void workManager::del_Emp()
{
	if (this->m_FileIsEmpty)
		cout << "文件不存在或记录为空\n";
	else
	{
		//按职工编号删除
		cout << "输入所删职工的编号\n";
		int id;
		cin >> id;
		
		int index = this->Isexist(id);
		if (index != -1)
		{
			//数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArr[i] = this->m_EmpArr[i + 1];
			}
			//更新数组中记录人员个数
			this->m_EmpNum--;
			//数据同步更新到文件中
			this->save();

			cout << "删除成功!\n";
		}
		else
			cout << "删除失败, 未找到该职工\n";
	}
	system("pause");
	system("cls");
}

int workManager::Isexist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (id == this->m_EmpArr[i]->m_Id)
		{
			index = i;
			break;
		}
	}
	return index;
}

void workManager::Isexistname(string name)
{
	bool flag = false;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (name == this->m_EmpArr[i]->m_Name)
		{
			cout << "查找成功，职工编号为："
				<< this->m_EmpArr[i]->m_Id
				<< "号的信息如下：\n";
			this->m_EmpArr[i]->showInfo();
			flag = true; 
		}
	}
	if (!flag)
		cout << "查无此人\n";
}

void workManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
		cout << "文件不存在或记录为空\n";
	else
	{
		cout << "输入所修改职工的编号\n";
		int id;
		cin >> id;

		int ret = this->Isexist(id);
		if (ret != -1)
		{
			//查找到了
			delete this->m_EmpArr[ret];

			int newid = 0;
			string newname = " ";
			int newselect = 0;

			cout << "查到：" << id << "号职工，请重新输入该职工的信息\n" << "请输入编号\n";
			cin >> newid;
			this->Ensure_consist(newid);

			cout << "请输入姓名：\n";
			cin >> newname;

			cout << "请输入岗位：\n";
			cout << "1.普通职工\n";
			cout << "2.经理\n";
			cout << "3.老板\n";
			cin >> newselect;

			Worker* worker = NULL;
			switch (newselect)
			{
			case 1:worker = new Employee(newid, newname, 1);
				break;
			case 2:worker = new Manager(newid, newname, 2);
				break;
			case 3:worker = new Boss(newid, newname, 3);
				break;
			default:
				break;
			}
			//更新数据到数组中
			this->m_EmpArr[ret] = worker;
			if (this->m_EmpArr[ret] != NULL)
			cout << "修改成功!\n";

			//保存到文件
			this->save();
		}
		else
			cout << "修改失败，查无此人\n";
	}
	system("pause");
	system("cls");
}

void workManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
		cout << "文件不存在或记录为空\n";
	else
	{
		cout << "请选择查找方式\n"
			<< "1. 按编号\n"
			<< "2. 按姓名\n";
		int select;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "请输入编号\n";
			cin >> id;
			int ret = this->Isexist(id);
			if (ret != -1)
				this->m_EmpArr[ret]->showInfo();
			else
				cout << "查无此人\n";
		}
		else if (select == 2)
		{
			string name;
			cout << "请输入姓名\n";
			cin >> name;

			this->Isexistname(name);
		}
		else
			cout << "输入有误\n";
	}
	system("pause");
	system("cls");
}

void workManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
		cout << "文件不存在或记录为空\n";
	else
	{
		cout << "请选择排序方式\n"
			<< "1.升序\n"
			<< "2.降序\n";
		int choice;
		cin >> choice;
		if (choice == 1)
			ascend_order(0, this->m_EmpNum - 1, this->m_EmpArr);
		else if (choice == 2)
			descend_order(0, this->m_EmpNum - 1, this->m_EmpArr);
		else
		{
			cout << "输入有误\n";
			system("pause");
			system("cls");
		}
		cout << "排序成功\n";
		this->save();
		//this->show_Emp();
	}
}

void workManager::ascend_order(int left, int right, Worker** m_EmpArr)
{
	if (left >= right)
		return;
	int q = left, p = right;
	while (q < p)
	{
		while (q < p && m_EmpArr[p]->m_Id >= m_EmpArr[left]->m_Id)
			p--;
		while (q < p && m_EmpArr[q]->m_Id <= m_EmpArr[left]->m_Id)
			q++;

		if (q == p)
			break;
		Worker* t = this->m_EmpArr[q];
		m_EmpArr[q] = m_EmpArr[p];
		m_EmpArr[p] = t;
	}
	if (q != left)
	{
		Worker* t = m_EmpArr[left];
		m_EmpArr[left] = m_EmpArr[p];
		m_EmpArr[p] = t;
	}

	ascend_order(left, q - 1, m_EmpArr);
	ascend_order(p + 1, right, m_EmpArr);
}

void workManager::descend_order(int left, int right, Worker** m_EmpArr)
{
	if (left >= right)
		return;
	int q = left, p = right;
	while (q < p)
	{
		while (q < p && m_EmpArr[p]->m_Id <= m_EmpArr[left]->m_Id)
			p--;
		while (q < p && m_EmpArr[q]->m_Id >= m_EmpArr[left]->m_Id)
			q++;

		if (q == p)
			break;
		Worker* t = this->m_EmpArr[q];
		m_EmpArr[q] = m_EmpArr[p];
		m_EmpArr[p] = t;
	}
	if (q != left)
	{
		Worker* t = m_EmpArr[left];
		m_EmpArr[left] = m_EmpArr[p];
		m_EmpArr[p] = t;
	}

	descend_order(left, q - 1, m_EmpArr);
	descend_order(p + 1, right, m_EmpArr);
}

void workManager::Clean_file()
{
	cout << "确认情况吗？\n"
		<< "1.确认\n"
		<< "2.返回\n";

	int choice;
	cin >> choice;

	if (choice == 1)
	{
		//打开模式ios::trunc,如果存在，删除并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArr != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArr != NULL)
					delete this->m_EmpArr[i];
			}

			this->m_EmpNum = 0;
			delete[] this->m_EmpArr;
			this->m_EmpArr = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功\n";
	}
	system("pause");
	system("cls");
}
