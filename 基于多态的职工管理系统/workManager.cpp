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
