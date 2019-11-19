#include "classter.h"
#include "queue.h"
#include <iostream>
#include <vector>
using namespace std;

TClasster::TClasster() : All_Task(0), Complite_Task(0), Error_Task(0), Downtime(0), Fail_Task(0), All_Time(0), Load_Proc(0)
{
	All_Tacts = 100;
	Size_Queue = 10;
	Intens = 1;
	Power = 1;
	All_Proc = 5;
	Free_Proc = 5;
}

TClasster::TClasster(int _tacts, int _sizequeue, double _intens, double _power, int _proc) : All_Task(0), Complite_Task(0), Error_Task(0), Downtime(0), Fail_Task(0), All_Time(0), Load_Proc(0)
{
	if (Size_Queue > MaxQueueSize)
		throw "ErrorSize";
	All_Tacts = _tacts;
	Size_Queue = _sizequeue;
	Intens = _intens;
	Power = _power;
	All_Proc = _proc;
	Free_Proc = _proc;
}

double TClasster::Random(int min, int max)
{
	std::mt19937_64 rng;
	uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{ uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
	rng.seed(ss);
	std::uniform_real_distribution<double> unif(min, max);
	return(unif(rng));
	//return double(rand()) / (RAND_MAX*RAND_MAX) * (max - min) + min;
}

Task TClasster::GetNewTask()
{
	Task tmp;
	//srand((unsigned int)time(NULL));
	tmp.Proc = Random(1, 10);
	//cout << tmp.Proc;
	tmp.Ticks = 1;
	return tmp;
}



bool TClasster::IsTask()
{
	//srand((unsigned int)time(NULL));
	double check = Random(0, 1);
	if (check <= Intens)
		return true;
	return false;
}

bool TClasster::IsComplete()
{
	//srand((unsigned int)time(NULL));
	double check = Random(0, 1);
	if (check <= Power)
		return true;
	return false;
}


void TClasster::Run()
{
	TQueue <Task> Queue(Size_Queue);
	for (int i = 0; i < All_Tacts; i++)
	{
		if (IsTask())
		{
			All_Task++;
			Task tmp = GetNewTask();
			if (tmp.Proc > All_Proc || Queue.IsFull())
				Error_Task++;
			else if (!Queue.IsFull())
				Queue.Push(tmp);
				
		}
		for (int j = 0; j < Jobs.size(); j++)
		{
			if (IsComplete())
			{
				Free_Proc += Jobs[j].Proc;
				All_Time += Jobs[j].Ticks;
				Complite_Task++;
				Jobs.erase(Jobs.begin() + j);
				j--;
			}
			else
				Jobs[j].Ticks++;
		}
		while (Queue.GetFirst().Proc <= Free_Proc && !Queue.IsEmpty())
		{
			Free_Proc -= Queue.GetFirst().Proc;
			Jobs.push_back(Queue.Pop());
		}
		Load_Proc = Load_Proc + (All_Proc - Free_Proc);
		if (Jobs.empty())
			Downtime++;
	}
	Fail_Task = Jobs.size() + Queue.GetCount();
}

void TClasster::Get_Status()
{
	cout << "__________________________________________________________" << endl << endl;
	cout << "Общее количество задач : " << All_Task << endl;
	cout << "Число завершенных задач : " << Complite_Task << endl;
	cout << "Число незавершенных задач : " << Fail_Task << endl;
	cout << "Число отклоненных задач : " << Error_Task << endl;
	if (Complite_Task != 0)
		cout << "Среднее время выполнение 1 задачи : " << double(All_Time) / double(Complite_Task) << endl;
	else
		cout << "Среднее время выполнение 1 задачи : " << 0 << endl;
	cout << "Процент отклоленных задач : " << (double(Error_Task) / All_Task) * 100 << "%" << endl;
	cout << "Процент бездействия класстера : " << (double(Downtime) / All_Tacts) * 100 << "%" << endl;
}
