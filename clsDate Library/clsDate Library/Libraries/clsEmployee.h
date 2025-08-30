#pragma once

#include <iostream>
#include "C:\Programming\Libraries\clsPerson.h"

using namespace std;

class clsEmployee : public clsPerson
{
private:
	string _title;
	float _salary;
	string _department;

public:
	clsEmployee(int ID, string firstName, string lastName, string email, string phoneNumber, string title, float salary, string department)
		: clsPerson(ID, firstName, lastName, email, phoneNumber)
	{
		_title = title;
		_salary = salary;
		_department = department;
	}

	string getTitle()
	{
		return _title;
	}
	void setTitle(string title)
	{
		_title = title;
	}
	__declspec(property(get = getTitle, put = setTitle)) string title;

	float getSalary()
	{
		return _salary;
	}
	void setSalary(float salary)
	{
		_salary = salary;
	}
	__declspec(property(get = getSalary, put = setSalary)) float salary;

	string getDepartment()
	{
		return _department;
	}
	void setDepartment(string department)
	{
		_department = department;
	}
	__declspec(property(get = getDepartment, put = setDepartment)) string department;

	void print()
	{
		cout << "Info :-" << endl;
		cout << "--------------------" << endl;
		cout << " ID          : " << getID() << endl;
		cout << " First Name  : " << getFirstName() << endl;
		cout << " Last Name   : " << getLastName() << endl;
		cout << " Full Name   : " << getFullName() << endl;
		cout << " E-Mail      : " << getEmail() << endl;
		cout << " Phone Number: " << getPhoneNumber() << endl;
		cout << " Title       : " << _title << endl;
		cout << " Department  : " << _department << endl;
		cout << " Salary      : " << _salary << endl;
		cout << "--------------------" << endl;
	}
};