#pragma warning(disable : 4996)
#pragma once

#include <iostream>
using namespace std;

#include "C:/Programming/Libraries/date_time.h"
using namespace date_time;


class clsDate
{
private:
	stDate _date;

public:
	clsDate()
	{
		_date = getSystemDate();
	}
	clsDate(string dateText)
	{
		_date = stringToDate(dateText);
	}
	clsDate(short day, short month, short year)
	{
		_date.day = day;
		_date.month = month;
		_date.year = year;
	}


	stDate getDate()
	{
		return _date;
	}
	void setDate(stDate date)
	{
		_date = date;
	}
	void setDate(string dateText)
	{
		_date = stringToDate(dateText);
	}
	void setDate(short day, short month, short year)
	{
		_date.day = day;
		_date.month = month;
		_date.year = year;
	}

	short getDay()
	{
		return _date.day;
	}
	void setDay(short day)
	{
		_date.day = day;
	}
	__declspec(property(get = getDay, put = setDay)) short day;

	short getMonth()
	{
		return _date.month;
	}
	void setMonth(short month)
	{
		_date.month = month;
	}
	__declspec(property(get = getMonth, put = setMonth)) short month;

	short getYear()
	{
		return _date.year;
	}
	void setYear(short year)
	{
		_date.year = year;
	}
	__declspec(property(get = getYear, put = setYear)) short year;

	void print(bool newLine = false)
	{
		printDate(_date, newLine);
	}

	static short getDayOrderOfWeek(stDate date)
	{
		return date_time::getDayOrderOfWeek(date);
	}

	short getDayOrderOfWeek()
	{
		return getDayOrderOfWeek(_date);
	}

	static void printMonthCalendar(stDate date)
	{
		date_time::printMonthCalendar(date);
	}

	static void printMonthCalendar(short year, short month)
	{
		printMonthCalendar({ 1,month, year });
	}

	void printMonthCalendar()
	{
		printMonthCalendar(_date);
	}

	static void printYearCalendar(stDate date)
	{
		date_time::printYearCalendar(date);
	}

	static void printYearCalendar(short year)
	{
		stDate date = { year, 1, 1 };
		printYearCalendar(date);
	}

	void printYearCalendar()
	{
		printYearCalendar(_date);
	}

	static short getNumberOfDaysFromBeginningOfYear(stDate date)
	{
		return date_time::getNumberOfDaysFromBeginningOfYear(date);
	}

	short getNumberOfDaysFromBeginningOfYear()
	{
		return getNumberOfDaysFromBeginningOfYear(_date);
	}

	void addDaysToDate(int daysToAdd)
	{
		_date = date_time::addDaysToDate(_date, daysToAdd);
	}

	bool isDateBeforeDate2(stDate date2)
	{
		return isDate1BeforeDate2(_date, date2);
	}

	bool isDateEqualToDate2(stDate date2)
	{
		return isDate1EqualToDate2(_date, date2);
	}

	bool isDateAfterDate2(stDate date2)
	{
		return isDate1AfterDate2(_date, date2);
	}

	bool isLastDayInMonth()
	{
		return date_time::isLastDayInMonth(_date);
	}

	bool isLastMonthInYear()
	{
		return date_time::isLastMonthInYear(_date.month);
	}

	void swapDates(stDate& date2)
	{
		date_time::swapDates(_date, date2);
	}

	int getDifferenceBetweenDates(stDate date2, bool includeEndDay = false)
	{
		return date_time::getDifferenceBetweenDates(_date, date2, includeEndDay);
	}

	bool isFirstDayInYear(short month, short day)
	{
		return date_time::isFirstDayInYear(_date.month, _date.day);
	}

	bool isFirstDayInMonth()
	{
		return date_time::isFirstDayInMonth(_date.day);
	}

	bool isFirstMonthInYear()
	{
		return date_time::isFirstDayInMonth(_date.day);
	}

	bool isLeapYear()
	{
		return date_time::isLeapYear(_date.year);
	}

	short dayOrderOfWeek()
	{
		return date_time::dayOrderOfWeek(_date);
	}

	bool isEndOfWeek()
	{
		return date_time::isEndOfWeek(dayOrderOfWeek());
	}

	bool isWeekend()
	{
		return date_time::isWeekend(dayOrderOfWeek());
	}

	bool isBusinessDay()
	{
		return date_time::isBusinessDay(dayOrderOfWeek());
	}

	short daysUntilEndOfWeek()
	{
		return date_time::daysUntilEndOfWeek(dayOrderOfWeek());
	}

	short daysUntilEndOfMonth(bool includeEndDay = false)
	{
		return date_time::daysUntilEndOfMonth(_date, includeEndDay);
	}

	short daysUntilEndOfYear(bool includeEndDay = false)
	{
		return date_time::daysUntilEndOfYear(_date, includeEndDay);
	}

	static int countVacationDays(stDate dateFrom, stDate dateTo)
	{
		return date_time::countVacationDays(dateFrom, dateTo);
	}

	int countVacationDays(stDate endVacationDays)
	{
		return countVacationDays(_date, endVacationDays);
	}

	static stDate getDateAfterTheEndOfVacation(stDate date, int vacationDays)
	{
		return date_time::getDateAfterTheEndOfVacation(date, vacationDays);
	}

	/*
		tawerghiii -> more methods (static, normal) are coming
	*/


};




