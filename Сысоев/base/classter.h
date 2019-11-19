#ifndef __POSTFIX_H__
#define __POSTFIX_H__
#include "queue.h"
#include <vector>
#include <time.h>
#include <chrono>
#include <random>

using namespace std;

struct Task
{
	int Ticks;
	int Proc;
};

class TClasster
{
private:
	int All_Tacts;  //Количество тактов
	int Size_Queue;  //очередь кластера
	double Intens;  //Интенсивность потока задач
	double Power;  //Мощность кластера
	
	int All_Task;  //Всего задач
	int Fail_Task;  //Число незавершенных задач
	int Complite_Task;  //Число завершенных задач
	int Error_Task;  //Число откланённых задач
	int Downtime;  //такты простоя 
	int All_Time;  //Все время выполнения всех задач

	int All_Proc;  //Всего процессоров
	int Free_Proc; //Свободные процессоры
	int Load_Proc;  //Загруженные процессоры

	vector<Task> Jobs;
	Task GetNewTask();
	double Random(int min, int max);
	bool IsTask();
	bool IsComplete();

public:
	TClasster();
	TClasster( int _tacts, int _sizequeue, double _intens, double _power, int _proc);
	void Run();
	void Get_Status();
};

#endif
