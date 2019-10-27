#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
	T* pMem;
	int size; //Размер стека
	int top;  //Позиция последнего элемента в стеке
public:

	TStack(int _size)
	{
		size = _size;
		top = -1;
		if ((size < 1) || (size > MaxStackSize))
			throw size;
		pMem = new T[size];
	}

	TStack(TStack& v)
	{
		size = v.size;
		top = v.top;
		pMem = new T[size];
		for (int i = 0; i < size; i++)
			pMem[i] = v.pMem[i];
	}

	~TStack()
	{ 
		delete [] pMem; 
	}

	bool IsEmpty() { return top == -1; }
	bool IsFull() { return top == (size - 1); }
	int GetSize() { return size; }  //Геттер
	int GetTop() { return top; }  //Геттер
	
	T Pop() //Взять элемент
	{
		if (!IsEmpty())
			return pMem[top--];
		else
			throw "Error";
	}

	T Top()  //Последний элемент
	{
		if (!IsEmpty())
			return pMem[top];
		else
			throw "Error";
	}

	void Push(T v) //Положить элемент
	{
		if (!IsFull())
			pMem[++top] = v;
		else
			throw "Error";
	}

	bool operator==(const TStack& v) const
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
	bool operator!=(const TStack& v) const { return!(*this == v); }
};

#endif
