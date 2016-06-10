#pragma once
#include"Stl_Iterator.h"
#include"TypeTraits.h"
#include"Stl_Construct.h"
#include"Stl_Iterator.h"
#include<memory.h>


template <class InputIterator, class ForwardIterator>
inline ForwardIterator
__UninitializedCopyAux(InputIterator first, InputIterator last,
	ForwardIterator result,
	__TrueType) {
	return copy(first, last, result);
}


template <class InputIterator, class ForwardIterator>
ForwardIterator
__UninitializedCopyAux(InputIterator first, InputIterator last,
	ForwardIterator result,
	__FalseType) {
	ForwardIterator cur = result;

	for (; first != last; ++first, ++cur)
		Construct(&*cur, *first);
	return cur;
}

template <class InputIterator, class ForwardIterator, class T>
inline ForwardIterator __UninitializedCopy(InputIterator first, InputIterator last,
	ForwardIterator result, T*) {
	typedef typename __TypeTraits<T>::is_POD_type is_POD;
	return __UninitializedCopyAux(first, last, result, is_POD());
}


template <class InputIterator, class ForwardIterator>
inline ForwardIterator UninitializedCopy(InputIterator first, InputIterator last,
	ForwardIterator result) {
	return __UninitializedCopy(first, last, result, ValueType(result));
}

inline char* UninitializedCopy(const char* first, const char* last,
	char* result) {
	memmove(result, first, last - first);
	return result + (last - first);
}

inline wchar_t* UninitializedCopy(const wchar_t* first, const wchar_t* last,
	wchar_t* result) {
	memmove(result, first, sizeof(wchar_t) * (last - first));
	return result + (last - first);
}



