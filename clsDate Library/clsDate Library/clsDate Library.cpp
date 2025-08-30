#include <iostream>
using namespace std;

#include "New folder/clsDate.h"

int main()
{

	clsDate date1;
	date1.print(true);

	clsDate date2("10/10/2001");
	date2.setDate(1, 1, 2009);
	cout << date2.isDateEqualToDate2({1, 1, 2222}) << endl;
	date2.print(true);

	clsDate date3(10, 10, 2001);
	date3.print(true);

	cout << "Date 3:\n";
	date3.printMonthCalendar();

	return 0;
}

