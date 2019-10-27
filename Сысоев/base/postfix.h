#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
	string infix;  
	string postfix; 
	bool IsOperator(char v);
	bool IsOperand(char v);
	int Priority(char a, char b);
	void InputStr(string& v);
	bool CheckOperations();
	bool CheckBrackets();
	void SplitStr(string& str);
public:
	TPostfix(string tmp = "")
	{
		infix = tmp; 
		postfix = "";
	}
	TPostfix(TPostfix& v)
	{
		infix = v.infix;
		postfix = v.postfix;
	}
	void Set(string& _infix)  //Сеттер
	{
		infix = _infix;
		postfix = "";
	}
	string GetInfix() { return infix; }  //Геттер инфиксной формы
	string GetPostfix() { return postfix; }  //Геттер постфиксной формы
	string ToPostfix();  //Перевод в постфиксную форму
	double Calculate(); // Ввод переменных, вычисление по постфиксной форме
};

#endif
