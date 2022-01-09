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
	void show_Emp();
	void del_Emp();
	int Isexist(int id);
	void Isexistname(string name);
	void Mod_Emp();
	void Find_Emp();
	void Sort_Emp();
	void ascend_order(int left, int right, Worker** m_EmpArr);
	void descend_order(int left, int right, Worker** m_EmpArr);
	void Ensure_consist(int Id);
	void Clean_file();
};
