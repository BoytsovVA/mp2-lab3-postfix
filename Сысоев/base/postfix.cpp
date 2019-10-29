#include "postfix.h"
#include "stack.h"
#include <iostream>
using namespace std;

bool TPostfix::IsOperator(char v)
{
	if (v == '+' || v == '*' || v == '-' || v == '/' || v =='(' || v == ')')
		return true;
	else
		return false;
}

bool TPostfix::IsOperand(char v)
{
	if ((int(v) >= 65 && int(v) <= 90) || (int(v) >= 97 && int(v) <= 122))
		return true;
	return false;
}

int TPostfix::Priority(char a, char b)
{
	if ((a == '*' || a == '/') && (b == '*' || b == '/') || (a == '+' || a == '-') && (b == '+' || b == '-'))
		return 0;  //0 приоритет -> одиннаковый
	if ((a == '*' || a == '/') && (b == '+' || b == '-'))
		return 1;  //1 приоритет -> a приоритетнее b
	if ((a == '+' || a == '-') && (b == '*' || b == '/'))
		return -1;  //-1 приоритет -> b приоритетнее a
	throw "not operation";
}

void TPostfix::InputStr(string& v)
{
	string str;
	for (int i = 0; i < v.size(); i++)
	{
		if (IsOperand(v[i]))
		{
			cout << "Введите переменную " << v[i] <<": ";
			cin >> str;
			char ch = v[i];
			int j = i;
			while (j < v.size())
			{
				if (ch == v[j])
				{
					v.erase(j, 1);
					v.insert(j, str);
					j += str.size();
				}
				else j++;
			}
		}
	}
}

bool TPostfix::CheckOperations()
{
	int Operands = 0, Operations = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
			Operations++;
		else if (!IsOperator(infix[i]))
		{
			while (infix[i] != '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/')
			{
				i++;
				if (i == infix.size())
					break;
			}
			i--;
			Operands++;
		}
	}
	if (Operands == Operations + 1)
		return true;
	else return false;
}

bool TPostfix::CheckBrackets()
{
	int LeftBrackets = 0, RightBrackets = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(')
			LeftBrackets++;
		else if (infix[i] == ')')
			RightBrackets++;
		if (RightBrackets > LeftBrackets)
			throw "Error Brackets";
	}
	if (LeftBrackets == RightBrackets)
		return true;
	else return false;
}


void TPostfix::SplitStr(string& str)
{
	if (str.back() != ',')
		str += ',';
}


string TPostfix::ToPostfix()
{
	if (!CheckBrackets())
		throw "Error Brackets";
	int count = -1;
	TStack<char> Oper(infix.size());
	for (int i = 0; i < infix.size(); i++)
	{
		if (IsOperator(infix[i]))
		{
			if (Oper.IsEmpty() || infix[i] == '(')
			{
				if (infix[i] != '(')
					SplitStr(postfix);
				Oper.Push(infix[i]);
				count++;
				continue;
			}
			else if (infix[i] == ')')
			{
				while (Oper.Top() != '(')
				{
					SplitStr(postfix);
					postfix += Oper.Pop();
					count--;
				}
				Oper.Pop();
				count--;
			}
			else if ((Oper.Top()) == '(' || Priority(infix[i], Oper.Top()) == 1)
			{
				Oper.Push(infix[i]);
				SplitStr(postfix);
				count++;
			}
			else if (Priority(infix[i], Oper.Top()) == -1)
			{
				SplitStr(postfix);
				while (!(Oper.IsEmpty()))
				{
					if (Oper.Top() == '(')
						break;
					postfix += Oper.Pop();
					SplitStr(postfix);
					count--;
				}
				Oper.Push(infix[i]);
				count++;
			}
			else if (Priority(infix[i], Oper.Top()) == 0)
			{
				SplitStr(postfix);
				postfix += Oper.Pop();
				Oper.Push(infix[i]);
				SplitStr(postfix);
			}
		}
		else
			postfix += infix[i];
		if (i == infix.size() - 1)
		{
			for (count; count >= 0; count--)
			{
				SplitStr(postfix);
				postfix += Oper.Pop();
			}
		}
	}
	return postfix;
}

double TPostfix::Calculate()
{
	if (!CheckOperations() || postfix == "")
		throw "Error Operand";
	InputStr(postfix);
	TStack<double> Res(infix.size());
	string str;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix[i] == ',')
			continue;
		if (!IsOperator(postfix[i]))
		{
			while (postfix[i] != ',')
			{
				str += postfix[i];
				i++;
			}
			Res.Push(atof(str.c_str()));  //Преобразуем строку в значение типа double. c_str нужно, чтобы конвертировать из string в const char*
			str = "";
		}
		else
		{
			double a = Res.Pop();
			double b = Res.Pop();
			if (postfix[i] == '+')
				Res.Push(b + a);
			else if (postfix[i] == '-')
				Res.Push(b - a);
			else if (postfix[i] == '*')
				Res.Push(b * a);
			else if (postfix[i] == '/')
			{
				if (a == 0.0)
					throw "Error Division";
				Res.Push(b / a);
			}
		}
	}
	return Res.Pop();
}
