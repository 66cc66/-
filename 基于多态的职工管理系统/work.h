#pragma once
#include<iostream>
using namespace std;

class Worker//职工抽象基类
{
public:
	//显示个人信息
	virtual void showInfo() = 0;
	//获取岗位名称
	virtual string getDeptName() = 0;

	//属性
	int m_Id;
	int m_DeptId;
	string m_Name;
};
