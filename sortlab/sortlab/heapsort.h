#pragma once
#include <functional>
#include <utility>

// 维护堆
template<typename Compare, typename Type>
void sift_down(Type* first, Type* __unused, Compare comp, int len, Type* start)
{
	// start 左子树 -> 2 * __start + 1
	// start 右子树 -> 2 * __start + 2
	int child = start - first;

	if (len < 2 || (len - 2) / 2 < child)
		return;

	// 左子树
	// 右子树 -> child + 1
	child = 2 * child + 1;      // 索引
	Type* child_i = first + child; // 指针

	// 比较左右子节点，child 就是最大那个
	if ((child + 1) < len && comp(*child_i, *(child_i + 1)))
	{
		// 右子存在并且比左子大
		++child_i;
		++child;
	}

	// 检查堆
	if (comp(*child_i, *start))
		// 成功，start > 最大的子元素
		return;

	Type top(std::move(*start)); // 缓存 旧top (交换 1)
	do
	{
		// 失败，交换亲本和最大的子元素
		*start = std::move(*child_i); // top 覆盖为子 (交换 2)
		start = child_i; // start 转为指向子
		
		if ((len - 2) / 2 < child)
			break;

		// 依据更新的亲本重新计算子元素
		child = 2 * child + 1;
		child_i = first + child;

		// 比较左右子节点，child 就是最大那个
		if ((child + 1) < len && comp(*child_i, *(child_i + 1)))
		{
			// 右子存在且比左子大
			++child_i;
			++child;
		}
		// 检查堆
	} while (!comp(*child_i, top));
	*start = std::move(top); // 旧 top 写入新的 top (旧的子节点) (交换 3)
}

// 交换首位元素 first, last - 1
// 重新维护堆 [first, last -1)
template<typename Type, typename Compare>
void pop_heap(Type* first, Type* last, Compare comp, int len)
{
	if (len > 1)
	{
		std::swap(*first, *--last);
		sift_down<Compare>(first, last, comp, len - 1, first);
	}
}

// 堆排序
template<typename Type, typename Compare>
void sort_heap(Type* first, Type* last, Compare comp)
{
	for (int n = last - first; n > 1; --last, --n)
		pop_heap(first, last, comp, n);
}

// 构造最大堆 [first, last)
template<typename Type, typename Compare>
void make_heap(Type* first, Type* last, Compare comp)
{
	int n = last - first;
	if (n > 1)
	{
		for (int start = (n - 2) / 2; start >= 0; --start)
		{
			sift_down<Compare>(first, last, comp, n, first + start);
		}
	}
}

template<typename Type>
void sort_heap(Type* first, Type* last)
{
	return sort_heap(first, last, std::less<Type>{});
}

template<typename Type>
void make_heap(Type* first, Type* last)
{
	return make_heap(first, last, std::less<Type>{});
}

template<typename Type, typename Compare>
void heapsort(Type* first, Type* last, Compare comp)
{
	make_heap(first, last, comp);
	sort_heap(first, last, comp);
}

template<typename Type>
void heapsort(Type* first, Type* last)
{
	heapsort(first, last, std::less<Type>{});
}