#include "employee.h"

Employee::Employee(int id, string name, int did)
{
	this->m_Id = id;
	this->m_DeptId = did;
	this->m_Name = name;
}

void Employee::showInfo()
{
	cout << "职工编号:  " << this->m_Id
		<< "   职工姓名:  " << this->m_Name
		<< "  岗位： " << this->getDeptName()
		<< " \t岗位职责：完成经理交给的任务\n";
}

string Employee::getDeptName()
{
	return string("员工");
}