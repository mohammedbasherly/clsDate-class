#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// enums
enum enNumberType { Odd = 1, Even = 2 };

// structures



namespace funcs {

	void printName(string name)
	{
		cout << "Your name is " << name << endl;
	}

	string readName(string msg = "What is your name? ")
	{
		string name;
		cout << msg;
		getline(cin, name);
		return name;
	}

	enNumberType checkNumberType(int number)
	{
		if (number % 2 == 0)
			return enNumberType::Even;
		return enNumberType::Odd;
	}

	void printNumberType(int number)
	{
		if (checkNumberType(number) == enNumberType::Even)
			cout << "Even";
		else
			cout << "Odd";
	}

	void printNumberType(enNumberType numberType)
	{
		if (numberType == enNumberType::Even)
			cout << "Even";
		else
			cout << "Odd";
	}

	float getHalfOfNumber(int number)
	{
		return (float)number / 2;
	}

	float getHalfOfNumber(float number)
	{
		return number / 2;
	}

	short readShortNumber(string msg = "Enter a short number: ")
	{
		short number;

		cout << msg;
		cin >> number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << msg;
			cin >> number;
		}

		return number;
	}

	short readPositiveShortNumber(string msg = "Enter a positive short number: ")
	{
		short number;

		do
		{
			cout << msg;
			cin >> number;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << msg;
				cin >> number;
			}
		} while (number <= 0);

		

		return number;
	}

	short readShortNumberInRange(short from, short to, string msg = "Enter a short number: ")
	{
		short num;
		do
		{
			cout << msg;
			cin >> num;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << msg;
				cin >> num;
			}
		} while (num < from || num > to);

		return num;
	}

	int readIntNumber(string msg = "Enter an integer number: ")
	{
		int number;

		cout << msg;
		cin >> number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << msg;
			cin >> number;
		}

		return number;
	}
	
	void printNumbersFrom1toN(int N)
	{
		for (int i = 1; i <= N; i++)
			cout << i << endl;
	}

	void printNumbersFromNto1(int N)
	{
		for (int i = N; i >= 1; i--)
			cout << i << endl;
	}

	int sumOddNumbersFrom1toN(int N)
	{
		int sum = 0;
		for (int i = 1; i <= N; i++)
		{
			if (checkNumberType(i) == enNumberType::Odd)
				sum += i;
		}
		return sum;
	}

	int sumEvenNumbersFrom1toN(int N)
	{
		int sum = 0;
		for (int i = 1; i <= N; i++)
		{
			if (checkNumberType(i) == enNumberType::Even)
				sum += i;
		}
		return sum;
	}

	int readPositiveIntNumber(string msg = "Enter a positive integer number: ")
	{
		int number;

		do
		{
			cout << msg;
			cin >> number;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << msg;
				cin >> number;
			}
		} while (number <= 0);

		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		return number;
	}

	int readIntNumberInRange(int from, int to, string msg = "Enter a positive integer number: ")
	{
		int number;

		do
		{
			cout << msg;
			cin >> number;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << msg;
				cin >> number;
			}
		} while (number < from || number > to);

		return number;
	}

	int factorialOfN(int N)
	{
		int result = 1;
		for (int i = N; i >= 2; i--)
			result *= i;

		return result;
	}

	float readFloatNumber(string msg = "Enter a float number: ")
	{
		float number;

		cout << msg;
		cin >> number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << msg;
			cin >> number;
		}

		return number;
	}

	float readPositiveFloatNumber(string msg = "Enter a positive float number: ")
	{
		float number;

		do
		{
			cout << msg;
			cin >> number;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << msg;
				cin >> number;
			}
		} while (number <= 0);

		return number;
	}

	float readFloatNumberInRange(float from, float to, string msg = "Enter a positive integer number: ")
	{
		float number;

		do
		{
			cout << msg;
			cin >> number;
			while (cin.fail())
			{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << msg;
				cin >> number;
			}
		} while (number < from || number > to);

		return number;
	}

	char readChar(string msg = "Enter a char: ")
	{
		char character;

		cout << msg;
		cin >> character;

		return character;
	}

	bool isPrime(int number)
	{
		if (number <= 1)
			return false;
		int M = sqrt(number);
		for (int i = 2; i <= M; i++)
		{
			if (number % i == 0)
				return false;
		}
		return true;
	}

	bool isPerfect(int number)
	{
		int sum = 0;
		for (int i = 1; i <= number / 2; i++)
		{
			if (number % i == 0)
				sum += i;
		}
		return sum == number;
	}

	short countDigitFrequency(int number, short digit)
	{
		number = abs(number);
		digit = abs(digit);
		short freq = 0, remainder;
		while (number > 0)
		{
			remainder = number % 10;
			number = number / 10;
			if (remainder == digit)
				freq++;
		}
		return freq;
	}

	void printAllDigitsFrequency(int number)
	{
		number = abs(number);
		short freq = 0;
		for (short i = 0; i <= 9; i++)
		{
			freq = countDigitFrequency(number, i);
			if (freq > 0)
				cout << "Digit [" << i << "] frequency is " << freq << " time(s).\n";
		}
	}

	int reverseNumber(int number)
	{
		int reverse = 0;
		while (number != 0)
		{
			reverse = reverse * 10 + number % 10;
			number = number / 10;
		}
		return reverse;
	}

	void printDigitsInReversedOrder(int number)
	{
		while (number != 0)
		{
			cout << number % 10 << endl;
			number = number / 10;
		}
	}

	void printDigitsInOrder(int number)
	{
		int reversedNumber = reverseNumber(number);
		printDigitsInReversedOrder(reversedNumber);
	}

	bool isPalindrome(int number)
	{
		return number == reverseNumber(number);
	}

	void printInvertedDigitPattern(short digit)
	{
		digit = abs(digit);
		for (short i = digit; i > 0; i--)
		{
			for (short j = 0; j < i; j++)
				cout << i;
			cout << endl;
		}
	}

	void printDigitPattern(short digit)
	{
		digit = abs(digit);
		for (short i = 1; i <= digit; i++)
		{
			for (short j = 0; j < i; j++)
				cout << i;
			cout << endl;
		}
	}

	int getRandomNumber(int from, int to)
	{
		return rand() % (to - from + 1) + from;
	}

}