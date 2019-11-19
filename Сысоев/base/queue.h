#ifndef __STACK_H__
#define __STACK_H__
using namespace std;
const int MaxQueueSize = 100;

template <class T>
class TQueue
{
private:
	T* pMem;
	int size; //Размер очереди 
	int last;
	int first;
	int count;
public:
	TQueue(int _size)
	{
		size = _size;
		first = -1;
		last = 0;
		count = 0;
		if ((size < 0) || (size > MaxQueueSize))
			throw size;
		pMem = new T[size];
	}

	TQueue(TQueue& v)
	{
		size = v.size;
		pMem = new T[size];
		count = v.count;
		first = v.first;
		last = v.last;
		for (int i = 0; i < size; i++)
			pMem[i] = v.pMem[i];
	}

	~TQueue()
	{ 
		delete [] pMem; 
	}

	bool IsEmpty() { return count == 0; }
	bool IsFull() { return count == size; }
	int GetSize() { return size; }  //Геттер
	int GetCount() { return count; }
	
	T Pop() //Взять элемент
	{
		if (!IsEmpty())
		{
			count--;
			first = (first+ 1) % size;
			return pMem[first];
		}
		else
			throw "Error";
	}


	void Push(T v) //Положить элемент
	{
		if (!IsFull())
		{
			count++;
			pMem[last] = v;
			last = (last + 1) % size;
		}
		else
			throw "Error";
	}

	T GetFirst() { return pMem[(first + 1) % size]; }
	T GetLast() { return pMem[last]; }

	TQueue& operator=(const TQueue& v)
	{
		if (size != v.size)
		{
			delete[] pMem;
			size = v.size;
			first = v.first;
			last = v.last;
			count = v.count;
			pMem = new T[size];
			for (int i = 0; i < size; i++)
				pMem[i] = v.pMem[i];
		}
		else
		{
			for (int i = 0; i < size; i++)
				pMem[i] = v.pMem[i];
			count = v.count;
			first = v.first;
			last = v.last;
		}
		return *this;
	}

	bool operator==(const TQueue& v) const
	{
		if (this->size != v.size)
			return false;
		else
		{
			for (int i = 0; i < size; i++)
			{
				if (this->pMem[i] != v.pMem[i])
					return false;
			}
			return true;
		}
	}
	bool operator!=(const TQueue& v) const { return!(*this == v); }

	
};

#endif
