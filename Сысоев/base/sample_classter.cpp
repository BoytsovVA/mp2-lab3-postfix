#include <iostream>
#include <string>
#include "classter.h"


using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int tacts, sizequeue, proc;
	double intens, power;
	cout << "Введите параметры класстера" << endl;

	cout << "Задайте время работы системы (В тактах)" << endl;
	cin >> tacts;

	cout << "Задайте размер очереди" << endl;
	cin >> sizequeue;

	cout << "Задайте мощность класстера" << endl;
	cin >> power;

	cout << "Задайте интенсивность потока задач" << endl;
	cin >> intens;

	cout << "Задайте количество процессоров в кластере" << endl;
	cin >> proc;

	TClasster classter(tacts, sizequeue, intens, power, proc);
	classter.Run();
	classter.Get_Status();

  return 0;
}
