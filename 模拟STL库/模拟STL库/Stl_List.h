#pragma once
#include"Stl_Iterator.h"



template<class T>
struct _List_Node
{
	_List_Node* _prev;
	_List_Node* _next;
	T _data;
	_List_Node()
	{

	}
	_List_Node(const T& x)
		:_data(x)
		,_prev(NULL)
		,_next(NULL)
	{

	}
};

template<class T,class Ref,class Ptr>
struct _List_Iterator
{
	typedef BidirectionalIterator_tag IteratorCategory;
	typedef _List_Iterator<T, T&, T*> Iterator;
	typedef T ValueType;
	typedef T& Reference;
	typedef T* Pointer;
	typedef _List_Node<T> *LinkType;
	typedef _List_Iterator<T, Ref, Ptr> Self;
	typedef int DifferenceType;
	LinkType _node;

	_List_Iterator()
	{

	}
	_List_Iterator(LinkType x)
		:_node(x)
	{

	}
	Reference operator*()
	{
		return _node->_data;
	}
	Pointer operator->()
	{
		return &(_node->_data);
	}
	Iterator operator++()
	{
		_node = _node->_next;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator tmp;
		tmp = *this;
		_node = _node->_next;
		return tmp;
	}

	Iterator operator--()
	{
		_node = _node->_prev;
		return *this;
	}
	Iterator operator--(int)
	{
		Iterator tmp = *this;
		_node = _node->_prev;
		return tmp;
	}

	bool operator!=(const Self& x)
	{
		return _node != x._node;
	}

	bool operator==(const Self& x)
	{
		return _node == x._node;
	}


};



template<class T, class Alloc=Alloc>
class List
{
public:
	typedef _List_Node<T>* LinkType;
	typedef _List_Iterator<T, T&, T*> Iterator;
	typedef SimpleAlloc<_List_Node, Alloc> ListNodeAllocator;
	List()
	{
		_node = new _List_Node<T>();
		_node->_next = _node;
		_node->_prev = _node;
	}
	~List()
	{
		Destory(Begin(), End());
		Iterator it = Begin();
		while (it != End())
		{
			ListNodeAllocator::Deallocate(it._node);
		}
	}


	Iterator Begin()
	{
		return _node->_next;
	}

	Iterator End()
	{
		return _node;
	}




	Iterator Insert(Iterator pos,const T& x)
	{
		LinkType prev = pos._node->_prev;
		LinkType tmp = ListNodeAllocator::Allocate();
		Construct(tmp, x);
		//LinkType tmp = new _List_Node<T>(x);
		prev->_next = tmp;
		pos._node->_prev = tmp;
		tmp->_next = pos._node;
		tmp->_prev = prev;
		return tmp;
	}


	void PushBack(const T& x)
	{
		Insert(End(), x);
	}


	void PushFront(const T& x)
	{
		Insert(Begin, x);
	}


	//reverse
	//remove
	//empty
	//size
	//unique
	//merge
protected:
	LinkType _node;
};




void TestList()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);

	List<int>::Iterator it;
	List<int>::Iterator begin = l.Begin();
	List<int>::Iterator end=l.End();
	for (it = l.Begin(); it != l.End(); it++)
	{
		cout << *it << " ";
	}
	cout << "Distance" << Distance(begin, end) << endl;
}