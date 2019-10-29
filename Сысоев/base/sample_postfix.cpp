#include <iostream>
#include <string>
#include "postfix.h"


using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	string expression;
	cout << "Введите арифметическое выражение: ";
	getline(cin, expression);
	cout << expression << endl;
	double res;
    //cout << "Введите арифметическое выражение: ";
    //cin >> expression;
    //cout << expression << endl;
	TPostfix postfix(expression);
    cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
    postfix.ToPostfix();
    cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
    res = postfix.Calculate();
    cout << res << endl;

  return 0;
}
