#pragma once

#include <iostream>
using namespace std;

#include "global_funcs.h";

class clsString
{
private:
	string _value;

public:
	clsString()
	{
		_value = "";
	}
	clsString(string value)
	{
		_value = value;
	}

	string getValue()
	{
		return _value;
	}
	void setValue(string value)
	{
		_value = value;
	}
	__declspec(property(get = getValue, put = setValue)) string value;

	static int countWords(string text)
	{
		return global_funcs::countWordsInText(text);
	}

	int countWords()
	{
		return global_funcs::countWordsInText(_value);
	}

	static char getFirstLetterOfWord(string word)
	{
		return global_funcs::getFirstLetterOfWord(word);
	}

	char getFirstLetterOfWord()
	{
		return getFirstLetterOfWord(_value);
	}

	static string getFirstWordFromText(string text)
	{
		return global_funcs::getFirstWordFromText(text);
	}

	string getFirstWordFromText()
	{
		return getFirstWordFromText(_value);
	}

	static void printFirstCharacterOfEachWordInText(string text, string delim = " ")
	{
		global_funcs::printFirstCharacterOfEachWordInText(text, delim);
	}

	void printFirstCharacterOfEachWordInText(string delim = " ")
	{
		printFirstCharacterOfEachWordInText(_value, delim);
	}

	static void uppercaseFirstLetterOfEachWordInText(string text)
	{
		global_funcs::uppercaseFirstLetterOfEachWordInText(text);
	}

	void uppercaseFirstLetterOfEachWordInText()
	{
		uppercaseFirstLetterOfEachWordInText(_value);
	}

	static void lowercaseFirstLetterOfEachWordInText(string text)
	{
		global_funcs::lowercaseFirstLetterOfEachWordInText(text);
	}

	void lowercaseFirstLetterOfEachWordInText()
	{
		lowercaseFirstLetterOfEachWordInText(_value);
	}

	static void uppercaseAllLetters(string text)
	{
		global_funcs::uppercaseAllLetters(text);
	}

	void uppercaseAllLetters()
	{
		uppercaseAllLetters(_value);
	}

	static void invertAllLettersCase(string &text)
	{
		global_funcs::invertAllLettersCase(text);
	}

	void invertAllLettersCase()
	{
		invertAllLettersCase(_value);
	}

	static short countCapitalLetters(string text)
	{
		return global_funcs::countCapitalLetters(text);
	}

	short countCapitalLetters()
	{
		return countCapitalLetters(_value);
	}

	static short countSmallLetters(string text)
	{
		return global_funcs::countSmallLetters(text);
	}

	short countSmallLetters()
	{
		return countSmallLetters(_value);
	}

	short countCharacter(char character, bool matchCase = true)
	{
		return global_funcs::countCharacterInString(_value, character, matchCase);
	}

	void printAllVowelLetters()
	{
		global_funcs::printAllVowelsInString(_value);
	}

	void printEachWordSeperatly(string seperator = "\n")
	{
		global_funcs::printEachWordSeperatlyInText(_value, seperator);
	}

	void splitIntoVector(vector<string> &vTokens, string delim = " ")
	{
		global_funcs::splitStringIntoVector(vTokens, _value, delim);
	}

	void trim_left()
	{
		_value = global_funcs::trim_left(_value);
	}

	void trim_right()
	{
		_value = global_funcs::trim_right(_value);
	}

	void trim()
	{
		_value = global_funcs::trim_(_value);
	}
	
	void reverseWords(string delim = " ")
	{
		_value = global_funcs::reverseWordsInString(_value, delim);
	}

	void replaceWordInString(string wordToReplace1, string wordToReplace2)
	{
		_value = global_funcs::replaceWordInString(_value, wordToReplace1, wordToReplace2);
	}

	void removeAllPuncuations()
	{
		_value = global_funcs::removeAllPuncuations(_value);
	}


};