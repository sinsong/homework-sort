#pragma once
#include <functional>

template<typename Type, typename Compare>
void shellsort(Type* first, Type* last, Compare comp)
{
	int len = last - first;
	for (int gap = len / 2; gap > 0; gap = gap / 2)
	{
		for (int i = gap; i < len; ++i)
		{
			int j = i;
			// gap 分隔的插入排序
			Type current = *(first + i);
			while (j - gap >= 0 && comp( current, *(first + j - gap)))
			{
				*(first + j) = *(first + j - gap);
				j = j - gap;
			}
			*(first + j) = current;
		}
	}
}

template<typename Type>
void shellsort(Type* first, Type* last)
{
	return shellsort(first, last, std::less<Type>{});
}