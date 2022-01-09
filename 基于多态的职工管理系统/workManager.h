#pragma once//防止头文件重复包含
#include<iostream>
using namespace std;
#include "work.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"
#include <fstream>
#define FILENAME "empFile.txt"

class workManager
{
public:
	workManager();
	void show_Menue();
	void exitSystem();
	void Add_Emp();
	void save();
	~workManager();
	int m_EmpNum;
	Worker** m_EmpArr;
	bool m_FileIsEmpty;
	int get_EmpNum();
	void init_Emp();
};
