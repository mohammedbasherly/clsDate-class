#pragma once


#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

#include "funcs.h"
#include "global_funcs.h"
#include "clients_data.h"

enum enDateCompare { Before = -1, Equal = 0, After = 1 };

struct stDate
{
	short year = 0;
	short month = 0;
	short day = 0;
};

struct stPeriod
{
	stDate startDate;
	stDate endDate;
};


namespace date_time {

	string textNumberOut(long long int number)
	{
		if (number < 10)
		{
			string numbers[10] =
			{
				"", "one", "two", "three",
				"four", "five", "six",
				"seven", "eight", "nine"
			};
			return numbers[number];
		}

		if (number < 20)
		{
			string numbers[10] =
			{
				"ten", "eleven", "twelve",
				"thirteen", "forteen", "fifteen",
				"sixteen", "seventeen", "eighteen",
				"ninteen"
			};
			return numbers[number - 10];
		}

		if (number < 100)
		{
			string numbers[8] =
			{
				"twenty", "thirty", "forty",
				"fifty", "sixty", "seventy",
				"eighty", "ninety"
			};
			return numbers[(number / 10) - 2] + " " + textNumberOut(number % 10);
		}

		if (number >= 100 && number <= 199)
		{
			return "one hundred " + textNumberOut(number % 100);
		}

		if (number < 1000)
		{
			return textNumberOut(number / 100) + " hundreds " + textNumberOut(number % 100);
		}

		if (number >= 1000 && number <= 1999)
		{
			return "one thousand " + textNumberOut(number % 1000);
		}

		if (number < 1000000)
		{
			return textNumberOut(number / 1000) + " thousands " + textNumberOut(number % 1000);
		}

		if (number >= 1000000 && number <= 1999999)
		{
			return "one million " + textNumberOut(number % 1000000);
		}

		if (number < 1000000000)
		{
			return textNumberOut(number / 1000000) + " millions " + textNumberOut(number % 1000000);
		}

		if (number >= 1000000000 && number <= 1999999999)
		{
			return "one billion " + textNumberOut(number % 1000000000);
		}

		if (number < 1000000000000)
		{
			return textNumberOut(number / 1000000000) + " billions " + textNumberOut(number % 1000000000);
		}

		return "Too Big Number!";
	}

	bool isLeapYear(short year)
	{
		return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
	}

	short numberOfDaysInYear(short year)
	{
		return isLeapYear(year) ? 366 : 365;
	}

	short numberOfHoursInYear(short year)
	{
		return numberOfDaysInYear(year) * 24;
	}

	int numberOfMinutesInYear(short year)
	{
		return numberOfHoursInYear(year) * 60;
	}

	int numberOfSecondsInYear(short year)
	{
		return numberOfMinutesInYear(year) * 60;
	}

	short numberOfDaysInMonth(short year, short month)
	{
		if (month < 1 || month > 12)
			return 0;
		short numberOfDays[12] = { 
			31, isLeapYear(year) ? 29 : 28, 31,
			30, 31, 30, 31,
			31, 30, 31, 30, 31
		};
		return numberOfDays[month - 1];

		/*
			Another way of solution:
			if (month < 1 || month > 12)
				return 0;
			short numberOfDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
			return (month == 2)? (isLeapYear(year)? 29 : 28) : (numberOfDays[month - 1]);
		*/

		/*
			Another way of solution :
			if (month < 1 || month > 12)
				return 0;
			if (month == 2)
				return isLeapYear(year)? 29 : 28;
			short arr31Days[7] = { 1, 3, 5, 7, 8, 10, 12 };
			for (short i = 0; i < 7; i++)
			{
				if (arr31Days[i] == month)
					return 31;
			}
			return 30;
		*/
	}

	short numberOfHoursInMonth(short year, short month)
	{
		return numberOfDaysInMonth(year, month) * 24;
	}

	int numberOfMinutesInMonth(short year, short month)
	{
		return numberOfHoursInMonth(year, month) * 60;
	}

	int numberOfSecondsInMonth(short year, short month)
	{
		return numberOfMinutesInMonth(year, month) * 60;
	}

	short getDayOrderOfWeek(short year, short month, short day)
	{
		if (year < 1)
			return -1;
		if (month < 1 || month > 12)
			return -1;
		if (day > numberOfDaysInMonth(year, month) || day < 1)
			return -1;

		short a = (14 - month) / 12;
		short y = year - a;
		short m = month + (12 * a) - 2;

		short d = (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
		return d;
	}

	short getDayOrderOfWeek(stDate date)
	{
		if (date.year < 1)
			return -1;
		if (date.month < 1 || date.month > 12)
			return -1;
		if (date.day > numberOfDaysInMonth(date.year, date.month) || date.day < 1)
			return -1;

		short a = (14 - date.month) / 12;
		short y = date.year - a;
		short m = date.month + (12 * a) - 2;

		short d = (date.day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
		return d;
	}

	string dayShortName(short dayOrderOfWeek)
	{
		if (dayOrderOfWeek < 0 || dayOrderOfWeek > 6)
			return "[Not a Day of Week]";
		string daysOfWeek[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return daysOfWeek[dayOrderOfWeek];
	}

	string monthShortName(short month)
	{
		string months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return months[month - 1];
	}

	void printMonthCalendar(short year, short month)
	{
		string space = "  ";
		cout << endl << space << "________________" << monthShortName(month) << "________________\n\n";
		cout << space << " Sun  Mon  Tue  Wed  Thu  Fri  Sat\n";

		short numberOfDays = numberOfDaysInMonth(year, month);
		short currentDay = getDayOrderOfWeek(year, month, 1);
		cout << space << " ";
		short i;
		for (i = 0; i < currentDay; i++)
		{
			cout << "     ";
		}
		for (short day = 1; day <= numberOfDays; day++)
		{
			cout << setw(3) << day << "  ";
			if (++i == 7)
			{
				cout << endl << space << " ";
				i = 0;
			}
		}
		cout << endl;
		cout << "  ___________________________________\n";
	}

	void printMonthCalendar(stDate date)
	{
		printMonthCalendar(date.year, date.month);
	}

	void printYearCalendar(short year)
	{
		cout << "\n  ___________________________________\n\n";
		cout << "             Calendar - " << year << endl;
		cout << "  ___________________________________\n";
		for (short month = 1; month <= 12; month++)
		{
			printMonthCalendar(year, month);
		}
	}

	void printYearCalendar(stDate date)
	{
		printYearCalendar(date.year);
	}


	short getNumberOfDaysFromBeginningOfYear(short year, short month, short day)
	{
		short totalDays = 0;
		for (short i = 1; i < month; i++)
		{
			totalDays += numberOfDaysInMonth(year, i);
		}
		totalDays += day;
		return totalDays;
	}

	short getNumberOfDaysFromBeginningOfYear(stDate date)
	{
		return getNumberOfDaysFromBeginningOfYear(date.year, date.month, date.day);
	}

	stDate readFullDate(string dayMSG = "Day: ", string monthMSG = "Month: ", string yearMSG = "Year: ")
	{
		stDate date;
		date.day = funcs::readShortNumberInRange(1, 31, dayMSG);
		date.month = funcs::readShortNumberInRange(1, 12, monthMSG);
		date.year = funcs::readPositiveShortNumber(yearMSG);
		return date;
	}

	stDate getDateFromNumberOfDaysFromBeginningOfYear(short numberOfDaysFromBeginningOfYear, short year)
	{
		stDate date;
		date.year = year;
		date.month = 1;
		short remainingDays = numberOfDaysFromBeginningOfYear;
		short monthDays;
		while (true)
		{
			monthDays = numberOfDaysInMonth(year, date.month);
			if (remainingDays > monthDays)
			{
				date.month++;
				remainingDays -= monthDays;
			}
			else
			{
				date.day = remainingDays;
				break;
			}
		}
		return date;
	}

	stDate addDaysToDate(stDate date, int daysToAdd)
	{
		int remainingDays = daysToAdd + getNumberOfDaysFromBeginningOfYear(date);
		date.month = 1;
		short monthDays;
		while (true)
		{
			monthDays = numberOfDaysInMonth(date.year, date.month);
			if (remainingDays > monthDays)
			{
				date.month++;
				remainingDays -= monthDays;
				if (date.month > 12)
				{
					date.month = 1;
					date.year++;
				}
			}
			else
			{
				date.day = remainingDays;
				break;
			}
		}
		return date;
	}

	void printDate(stDate date, bool newLine = false)
	{
		cout << date.day << "/" << date.month << "/" << date.year;
		newLine ? cout << endl : cout << " ";
	}

	bool isDate1BeforeDate2(stDate date1, stDate date2)
	{
		return (date1.year < date2.year) ? true : ((date1.year == date2.year)? (date1.month < date2.month? true : (date1.month == date2.month? (date1.day < date2.day) : false)) : false);
	}

	bool isDate1EqualToDate2(stDate date1, stDate date2)
	{
		return date1.year == date2.year? (date1.month == date2.month? (date1.day == date2.day) : false) : false;
	}

	bool isLastDayInMonth(stDate date)
	{
		return date.day == numberOfDaysInMonth(date.year, date.month);
	}

	bool isLastMonthInYear(short month)
	{
		return month == 12;
	}

	bool isLastMonthInYear(stDate date)
	{
		return date.month == 12;
	}

	stDate increaseDateByOneDay(stDate date)
	{
		if (isLastDayInMonth(date))
		{
			date.day = 1;
			if (isLastMonthInYear(date.month))
			{
				date.year++;
				date.month = 1;
			}
			else
				date.month++;
		}
		else
			date.day++;

		return date;
	}

	void swapDates(stDate &date1, stDate &date2)
	{
		stDate tempDate = date1;
		date1 = date2;
		date2 = tempDate;
	}

	int getDifferenceBetweenDates(stDate date1, stDate date2, bool includeEndDay = false)
	{
		short swapFlagValue = 1;
		if (!isDate1BeforeDate2(date1, date2))
		{
			swapDates(date1, date2);
			swapFlagValue = -1;
		}

		int counter = 0;
		while (isDate1BeforeDate2(date1, date2))
		{
			date1 = increaseDateByOneDay(date1);
			counter++;
		}

		return includeEndDay ? ++counter * swapFlagValue : counter * swapFlagValue;
	}

	stDate getSystemDate()
	{
		stDate date;

		time_t t = time(0);
		tm nowStruct;                    // Create a tm object
		localtime_s(&nowStruct, &t);     // Fill it safely

		date.day = nowStruct.tm_mday;
		date.month = nowStruct.tm_mon + 1;
		date.year = nowStruct.tm_year + 1900;

		return date;
	}


	stDate increaseDateByXDays(stDate date, int daysToAdd)
	{
		for (int i = 0; i < daysToAdd; i++)
		{
			date = increaseDateByOneDay(date);
		}
		return date;
	}

	stDate increaseDateByOneWeek(stDate date)
	{
		return increaseDateByXDays(date, 7);
	}

	stDate increaseDateByXWeeks(stDate date, int weeks)
	{
		for (int i = 0; i < weeks; i++)
		{
			date = increaseDateByOneWeek(date);
		}
		return date;
	}

	stDate increaseDateByOneMonth(stDate date)
	{
		if (isLastMonthInYear(date.month))
		{
			date.month = 1;
			date.year++;
		}
		else
			date.month++;

		short maxDaysInMonth = numberOfDaysInMonth(date.year, date.month);
		if (date.day > maxDaysInMonth)
			date.day = maxDaysInMonth;

		return date;
	}

	stDate increaseDateByXMonths(stDate date, int months)
	{
		for (int i = 0; i < months; i++)
		{
			date = increaseDateByOneMonth(date);
		}
		return date;
	}

	stDate increaseDateByOneYear(stDate date)
	{
		date.year++;
		return date;
	}

	stDate increaseDateByXYears(stDate date, short years)
	{
		for (short i = 0; i < years; i++)
		{
			date = increaseDateByOneYear(date);
		}
		return date;
	}

	stDate increaseDateByXYears_faster(stDate date, short years)
	{
		date.year += years;
		return date;
	}

	stDate increaseDateByOneDecade(stDate date)
	{
		date.year += 10;
		return date;
	}

	stDate increaseDateByXDecades(stDate date, short decades)
	{
		for (short i = 0; i < decades; i++)
			date = increaseDateByOneDecade(date);
		return date;
	}

	stDate increaseDateByXDecades_faster(stDate date, short decades)
	{
		date.year += (decades * 10);
		return date;
	}

	stDate increaseDateByOneCentury(stDate date)
	{
		date.year += 100;
		return date;
	}

	stDate increaseDateByOneMillenium(stDate date)
	{
		date.year += 1000;
		return date;
	}

	bool isFirstDayInYear(short month, short day)
	{
		return (day == 1 && month == 1);
	}

	bool isFirstDayInMonth(short day)
	{
		return day == 1;
	}

	bool isFirstMonthInYear(short month)
	{
		return month == 1;
	}

	stDate decreaseDateByOneDay(stDate date)
	{
		if (isFirstDayInMonth(date.day))
		{
			if (isFirstMonthInYear(date.month))
			{
				date.day = 31;
				date.month = 12;
				if (date.year > 1)
					date.year--;
			}
			else
			{
				date.month--;
				date.day = numberOfDaysInMonth(date.year, date.month);
			}
		}
		else
			date.day--;

		return date;
	}

	stDate decreaseDateByXDays(stDate date, int days)
	{
		for (int i = 0; i < days; i++)
		{
			date = decreaseDateByOneDay(date);
		}
		return date;
	}

	stDate decreaseDateByOneWeek(stDate date)
	{
		return decreaseDateByXDays(date, 7);
	}

	stDate decreaseDateByXWeeks(stDate date, int weeks)
	{
		return decreaseDateByXDays(date, weeks * 7);
	}

	stDate decreaseDateByOneMonth(stDate date)
	{
		if (isFirstMonthInYear(date.month))
		{
			date.month = 12;
			date.year--;
		}
		else
			date.month--;

		short maxDaysInMonth = numberOfDaysInMonth(date.year, date.month);
		if (date.day > maxDaysInMonth)
			date.day = maxDaysInMonth;

		return date;
	}

	stDate decreaseDateByXMonths(stDate date, int months)
	{
		for (int i = 0; i < months; i++)
		{
			date = decreaseDateByOneMonth(date);
		}
		return date;
	}

	stDate decreaseDateByOneYear(stDate date)
	{
		if (date.year > 1)
			date.year--;
		return date;
	}

	stDate decreaseDateByXYears(stDate date, int years)
	{
		for (int i = 0; i < years; i++)
			date = decreaseDateByOneYear(date);
		return date;
	}

	stDate decreaseDateByXYears_faster(stDate date, int years)
	{
		date.year -= years;
		if (date.year < 1)
			date.year = 1;
		return date;
	}

	stDate decreaseDateByOneDecade(stDate date)
	{
		return decreaseDateByXYears_faster(date, 10);
	}

	stDate decreaseDateByXDecades(stDate date, int decades)
	{
		for (int i = 0; i < decades; i++)
			date = decreaseDateByOneDecade(date);
		return date;
	}

	stDate decreaseDateByXDecades_faster(stDate date, int decades)
	{
		return decreaseDateByXYears_faster(date, decades * 10);
	}

	stDate decreaseDateByOneCentury(stDate date)
	{
		return decreaseDateByXYears_faster(date, 100);
	}

	stDate decreaseDateByOneMillenium(stDate date)
	{
		return decreaseDateByXYears_faster(date, 1000);
	}

	short dayOrderOfWeek(stDate date)
	{
		return getDayOrderOfWeek(date.year, date.month, date.day);
	}

	bool isEndOfWeek(short dayOrder)
	{
		return dayOrder == 5;
	}

	bool isEndOfWeek(stDate date)
	{
		return isEndOfWeek(dayOrderOfWeek(date));
	}

	bool isWeekend(short dayOrder)
	{
		return dayOrder == 5 || dayOrder == 6;
	}

	bool isWeekend(stDate date)
	{
		return isWeekend(dayOrderOfWeek(date));
	}

	bool isBusinessDay(short dayOrder)
	{
		return !isWeekend(dayOrder);
	}

	bool isBusinessDay(stDate date)
	{
		return isBusinessDay(dayOrderOfWeek(date));
	}

	short daysUntilEndOfWeek(short dayOrder)
	{
		if (dayOrder != 6)
			return 5 - dayOrder;
		return 6;
	}

	short daysUntilEndOfWeek(stDate date)
	{
		return daysUntilEndOfWeek(dayOrderOfWeek(date));
	}

	short daysUntilEndOfMonth(stDate date, bool includeEndDay = false)
	{
		return includeEndDay? 1 + numberOfDaysInMonth(date.year, date.month) - date.day : numberOfDaysInMonth(date.year, date.month) - date.day;
	}

	short daysUntilEndOfYear(stDate date, bool includeEndDay = false)
	{
		return includeEndDay? 1 + numberOfDaysInYear(date.year) - getNumberOfDaysFromBeginningOfYear(date) : numberOfDaysInYear(date.year) - getNumberOfDaysFromBeginningOfYear(date);
	}

	int countVacationDays(stDate dateFrom, stDate dateTo)
	{
		if (!isDate1BeforeDate2(dateFrom, dateTo))
			return -1;
		int counter = 0;
		while (isDate1BeforeDate2(dateFrom, dateTo))
		{
			dateFrom = increaseDateByOneDay(dateFrom);
			if (isBusinessDay(dateFrom))
				counter++;
		}
		return counter;
	}

	stDate getDateAfterTheEndOfVacation(stDate date, int vacationDays)
	{
		while (isWeekend(date))
		{
			date = increaseDateByOneDay(date);
		}

		while (true)
		{
			if (vacationDays < 1)
				break;
			if (isBusinessDay(date))
				vacationDays--;
			date = increaseDateByOneDay(date);
		}

		while (isWeekend(date))
		{
			date = increaseDateByOneDay(date);
		}

		return date;
	}

	bool isDate1AfterDate2(stDate date1, stDate date2)
	{
		return !isDate1BeforeDate2(date1, date2) && !isDate1EqualToDate2(date1, date2);
	}

	enDateCompare compareDates(stDate date1, stDate date2)
	{
		if (isDate1BeforeDate2(date1, date2))
			return enDateCompare::Before;
		if (isDate1EqualToDate2(date1, date2))
			return enDateCompare::Equal;
		return enDateCompare::After;
	}

	stPeriod readPeriod(string dayMSG = "Day: ", string monthMSG = "Month: ", string yearMSG = "Year: ")
	{
		stPeriod period;

		cout << "Start Date:\n\n";
		period.startDate = readFullDate(dayMSG, monthMSG, yearMSG);
		cout << endl;
		cout << "End Date:\n\n";
		period.endDate = readFullDate(dayMSG, monthMSG, yearMSG);
		
		if (compareDates(period.startDate, period.endDate) == enDateCompare::After)
			swapDates(period.startDate, period.endDate);

		return period;
	}

	bool does2PeriodsOverlap(stPeriod period1, stPeriod period2)
	{
		if (compareDates(period2.startDate, period1.endDate) == enDateCompare::After)
			return false;
		if (compareDates(period1.startDate, period2.endDate) == enDateCompare::After)
			return false;
		return true;
	}

	int periodLengthInDays(stPeriod period, bool includeEndDay = false)
	{
		return getDifferenceBetweenDates(period.startDate, period.endDate, includeEndDay);
	}

	bool isDateWithinPeriod(stPeriod period, stDate date)
	{
		return !(compareDates(date, period.startDate) == enDateCompare::Before
			||
				compareDates(date, period.endDate) == enDateCompare::After);
	}

	int countOverlapDays(stPeriod period1, stPeriod period2, bool includedEndDay = false)
	{
		if (!does2PeriodsOverlap(period1, period2))
			return 0;

		if (isDateWithinPeriod(period2, period1.startDate))
		{
			if (isDateWithinPeriod(period2, period1.endDate))
				return getDifferenceBetweenDates(period1.startDate, period1.endDate, includedEndDay);
			else
				return getDifferenceBetweenDates(period1.startDate, period2.endDate, includedEndDay);
		}
		return getDifferenceBetweenDates(period2.startDate, period1.endDate, includedEndDay);
	}

	bool isValidDate(stDate date)
	{
		if (date.year < 1)
			return false;
		if (date.month < 1 || date.month > 12)
			return false;
		return !(date.day < 1 || date.day > numberOfDaysInMonth(date.year, date.month));
	}

	stDate stringToDate(string textDate)
	{
		stDate date;
		vector<string> vDate = global_funcs::splitStringIntoVector(textDate, "/");
		date.day = stoi(vDate[0]);
		date.month = stoi(vDate[1]);
		date.year = stoi(vDate[2]);
		return date;
	}

	string dateToString(stDate date)
	{
		return to_string(date.day) + "/" + to_string(date.month) + "/" + to_string(date.year);
	}
	
	string formatDate(stDate date, string format = "dd/mm/yyyy")
	{
		string formattedDate = "";

		formattedDate = global_funcs::replaceWordInString(format, "dd", to_string(date.day));
		formattedDate = global_funcs::replaceWordInString(formattedDate, "mm", to_string(date.month));
		formattedDate = global_funcs::replaceWordInString(formattedDate, "yyyy", to_string(date.year));

		return formattedDate;
	}

}