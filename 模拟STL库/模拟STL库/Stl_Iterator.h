#pragma once


struct InputIterator_tag {};
struct OutputIterator_tag {};
struct ForwardIterator_tag : public InputIterator_tag {};
struct BidirectionalIterator_tag : public ForwardIterator_tag {};
struct RandomAccessIterator_tag : public bidirectional_iterator_tag {};

template <class T, class Distance> struct InputIterator {
	typedef InputIterator_tag IteratorCategory;
	typedef T                  ValueType;
	typedef Distance           DifferenceType;
	typedef T*                 Pointer;
	typedef T&                 Reference;
};

struct OutputIterator {
	typedef OutputIterator_tag IteratorCategory;
	typedef void                ValueType;
	typedef void                DifferenceType;
	typedef void                Pointer;
	typedef void                Reference;
};

template <class T, class Distance> struct ForwardIterator {
	typedef ForwardIterator_tag IteratorCategory;
	typedef T                    ValueType;
	typedef Distance             DifferenceType;
	typedef T*                   Pointer;
	typedef T&                   Reference;
};


template <class T, class Distance> struct BidirectionalIterator {
	typedef BidirectionalIterator_tag IteratorCategory;
	typedef T                          ValueType;
	typedef Distance                   DifferenceType;
	typedef T*                         Pointer;
	typedef T&                         Reference;
};

template <class T, class Distance> struct RandomAccessIterator {
	typedef RandomAccessIterator_tag IteratorCategory;
	typedef T                          ValueType;
	typedef Distance                   DifferenceType;
	typedef T*                         Pointer;
	typedef T&                         Reference;
};



template <class Category, class T, class Distance = size_t,class Pointer = T*, class Reference = T&>
struct Iterator {
	typedef Category  IteratorCategory;
	typedef T         ValueType;
	typedef Distance  DifferenceType;
	typedef Pointer   Pointer;
	typedef Reference Reference;
};


template <class Iterator>
struct IteratorTraits {
	typedef typename Iterator::IteratorCategory IteratorCategory;
	typedef typename Iterator::ValueType        ValueType;
	typedef typename Iterator::DifferenceType   DifferenceType;
	typedef typename Iterator::Pointer           Pointer;
	typedef typename Iterator::Reference         Reference;
};//类型萃取机

template<class InputIterator>
int Distance(InputIterator first, InputIterator last)
{
	return _Distance(first, last, IteratorTraits<InputIterator>::IteratorCategory());
}


template<class InputIterator>
int _Distance(InputIterator first, InputIterator last, ForwardIterator_tag)
{
	int count = 0;
	while (first != last)
	{
		count++;
		first++;
	}
	return count;
}


template<class InputIterator>
int _Distance(InputIterator first, InputIterator last, RandomAccessIterator_tag)
{
	return last - first;
}
