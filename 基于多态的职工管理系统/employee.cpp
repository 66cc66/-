#include "employee.h"

Employee::Employee(int id, string name, int did)
{
	this->m_Id = id;
	this->m_DeptId = did;
	this->m_Name = name;
}

void Employee::showInfo()
{
	cout << "ְ�����:  " << this->m_Id
		<< "   ְ������:  " << this->m_Name
		<< "  ��λ�� " << this->getDeptName()
		<< " \t��λְ����ɾ�����������\n";
}

string Employee::getDeptName()
{
	return string("Ա��");
}