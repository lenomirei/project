#pragma once
#include<cassert>
#include"Stl_Iterator.h"
#include"Stl_Alloc.h"
#include"Stl_Construct.h"
#include"Stl_Uninittialized.h"



template<class T, class Alloc=Alloc>
class Vector
{
	typedef T ValueType;
	typedef T& Reference;
	typedef T* Pointer;
	typedef int DifferenceType;
public:
	typedef ValueType * Iterator;
	typedef RandomAccessIterator_tag IteratorCategory;
	typedef SimpleAlloc<T, Alloc> DataAlloc;



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
		Destory(Start, Finish);
		DataAlloc::Deallocate(Start, Size());
	}
	

	

	/*void Insert(Iterator Position,size_t n,const ValueType& x)
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
	}*/
	void Push_Back(const T& x)
	{
		ExpandCapacity();
		Construct(Finish,x);
		Finish++;

	}
	void Pop_Back()
	{
		assert(Size());
		Destory(Finish);//有必要么？？
		--Finish;
	}
	size_t Size()
	{
		return (Finish - Start);
	}

	bool Empty()
	{
		return Beign == End;
	}

	Iterator Erase(Iterator pos)
	{
		Iterator begin = pos;
		wihle(begin + 1 != Finish)
		{
			*begin = *(beign + 1);
		}
		--Finish;
		return pos;
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
			size_t size = Size();
			size_t curLength = EndOfStorage - Start;
			size_t newLength = 2 * curLength + 3;
			T *tmp = DataAlloc::Allocate(newLength);
			if (Start)
			{
				UninitializedCopy(Start, Start + size, tmp);
			}
			Destory(Start, Finish);
			DataAlloc::Deallocate(Start, EndOfStorage - Start);

			Start = tmp;
			Finish = Start + Size();
			EndOfStorage = Start + newLength;

		/*	Iterator newStart = new T[newLength];
			Iterator it = Begin();
			for (int i = 0; i < Size(); ++i)
			{
				newStart[i] = Start[i];
			}
			Destory();
			Start = newStart;
			Finish = Start + curLength;
			EndOfStorage = Start + newLength;*/
		}
	}
	//void Destory()
	//{
	//	delete[] Start;
	//	Start = NULL;
	//	Finish = NULL;
	//	EndOfStorage = NULL;
	//}
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
	Vector<int>::Iterator cur;
	for (cur = v.Begin(); cur != v.End(); cur++)
	{
		cout << *cur << " ";
	}
}