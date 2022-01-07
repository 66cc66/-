#pragma once
#include<iostream>
using namespace std;
#include "work.h"

class Employee : public Worker
{
public:
	Employee(int id, string name, int did);
	void showInfo();
	string getDeptName();

};
