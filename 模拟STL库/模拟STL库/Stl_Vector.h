#pragma once
#include<cassert>

template<class T>
class Vector
{
	typedef T ValueType;
public:
	typedef ValueType * Iterator;
	Iterator Begin() { return Start; }
	Iterator End() { return Finish; }

	Vector()
		:Start(NULL)
		,Finish(NULL)
		,EndOfStorage(NULL)
	{

	}
	Vector(size_t n,const T& value)
	{
		Start = new T[n];
		Finish = Start + n;
		EndOfStorage = Finish;
	}
	~Vector()
	{
		Destory();
	}
	

	

	void Insert(Iterator Position,size_t n,const ValueType& x)
	{
		if (n != 0)
		{
			if (size_t(EndOfStorage - Finish) > n)
			{
				size_t Elems_After = Finish - Position;
				Iterator OldFinish = Finish;
				if (Elems_After > n)
				{
					Finish += n;
					Copy_Backward(Position, OldFinish - n, OldFinish);
					while (n-- > 0)
					{
						*(Position++) = x;
					}
				}
				else
				{
					int tmp = n - Elems_After;
					while (tmp-- > 0)
					{
						*(Finish++) = x;
					}
					tmp = OldFinish - Position;
					for (int i = 0; i < tmp; ++i)
					{
						*(Finish++) = *(Position + i);
					}
					while (n-- > 0)
					{
						*(Position++) = x;
					}
				}
			}
			else
			{
				ExpandCapacity();
				Insert(Position, n, x);
			}
		}
	}
	void Push_Back(const T& x)
	{
		ExpandCapacity();
		*(Finish++) = x;

	}
	void Pop_Back()
	{
		assert(Size());
		--Finish;
		Finish->~T();
	}
	size_t Size()
	{
		return (Finish - Start);
	}

	bool Empty()
	{
		return Beign == End;
	}



	

protected:

	void Copy_Backward(Iterator Position, Iterator first,Iterator last)
	{
		while (first != Position - 1)
		{
			*(last--) = *(first--);
		}

	}
	void ExpandCapacity()
	{
		if (Finish == EndOfStorage)
		{
			size_t curLength = EndOfStorage - Start;
			size_t newLength = 2 * curLength + 1;
			Iterator newStart = new T[newLength];
			Iterator it = Begin();
			for (int i = 0; i < Size(); ++i)
			{
				newStart[i] = Start[i];
			}
			Destory();
			Start = newStart;
			Finish = Start + curLength;
			EndOfStorage = Start + newLength;
		}
	}
	void Destory()
	{
		delete[] Start;
		Start = NULL;
		Finish = NULL;
		EndOfStorage = NULL;
	}
protected:
	Iterator Start;
	Iterator Finish;
	Iterator EndOfStorage;
};


void TestVector()
{
	Vector<int> v;
	v.Push_Back(1);
	v.Push_Back(2);
	v.Push_Back(3);
	v.Push_Back(4);
	v.Push_Back(5);
	Vector<int>::Iterator it;
	it = v.Begin();
	it++;
	it++;
	v.Insert(it, 1, 6);
	Vector<int>::Iterator cur;
	for (cur = v.Begin(); cur != v.End(); cur++)
	{
		cout << *cur << " ";
	}
}