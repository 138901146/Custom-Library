//
// Created by 박우현 on 2024-11-20.
//
#include "LazyPropagationSegmentTree.h"

LazyPropagationSegmentTree::LazyPropagationSegmentTree() { }

LazyPropagationSegmentTree::~LazyPropagationSegmentTree()
{
	if(tree != nullptr)
	{
		delete tree;
	}
	if(lazy != nullptr)
	{
		delete lazy;
	}

	tree = nullptr;
	lazy = nullptr;
}

bool LazyPropagationSegmentTree::initialize(int type,int size,long long *array)
{
	if(isInvalidType(type))
	{
		return false;
	}

	this->type = type;
	leftmost = 0;
	rightmost = size;

	treeSize = 0;
	while((1 << treeSize) < rightmost)
	{
		++treeSize;
	}
	treeSize = 1 << ++treeSize;

	tree = new long long[treeSize];
	lazy = new long long[treeSize]();

	switch(getType())
	{
		case MIN:
			initializeMin(array,1,leftmost,rightmost);
			break;
		case MAX:
			initializeMax(array,1,leftmost,rightmost);
			break;
		case SUM:
			initializeSum(array,1,leftmost,rightmost);
			break;
		case AND:
			initializeAnd(array,1,leftmost,rightmost);
			break;
		case OR:
			initializeOr(array,1,leftmost,rightmost);
			break;
		case XOR:
			initializeXor(array,1,leftmost,rightmost);
			break;
		default:
			break;
	}

	return true;
}

long long LazyPropagationSegmentTree::get(int left,int right)
{
	long long value;

	if(isInvalidIndex(left) || isInvalidIndex(right) || right < left)
	{
		return -1;	// TODO: 만약 결과값이 진짜 -1인 경우 문제 발생 -> 추후 학습 후 ERROR CODE 생성 또는 throw 등으로 변경 요망.
	}

	switch(getType())
	{
		case MIN:
			value = getMin(1,leftmost,rightmost,left,right);
			break;
		case MAX:
			value = getMax(1,leftmost,rightmost,left,right);
			break;
		case SUM:
			value = getSum(1,leftmost,rightmost,left,right);
			break;
		case AND:
			value = getAnd(1,leftmost,rightmost,left,right);
			break;
		case OR:
			value = getOr(1,leftmost,rightmost,left,right);
			break;
		case XOR:
			value = getXor(1,leftmost,rightmost,left,right);
			break;
		default:
			return -1;	// TODO: 만약 결과값이 진짜 -1인 경우 문제 발생 -> 추후 학습 후 ERROR CODE 생성 또는 throw 등으로 변경 요망.
	}

	return value;
}

bool LazyPropagationSegmentTree::update(int left,int right,long long diff)
{
	if(isInvalidIndex(left) || isInvalidIndex(right) || right < left)
	{
		return false;
	}

	switch(getType())
	{
		case MIN:
			updateMin(1,leftmost,rightmost,left,right,diff);
			break;
		case MAX:
			updateMax(1,leftmost,rightmost,left,right,diff);
			break;
		case SUM:
			updateSum(1,leftmost,rightmost,left,right,diff);
			break;
		case AND:
			updateAnd(1,leftmost,rightmost,left,right,diff);
			break;
		case OR:
			updateOr(1,leftmost,rightmost,left,right,diff);
			break;
		case XOR:
			updateXor(1,leftmost,rightmost,left,right,diff);
			break;
		default:
			return false;
	}

	return true;
}

int LazyPropagationSegmentTree::getType()
{
	return type;
}

int LazyPropagationSegmentTree::getTreeSize()
{
	return treeSize;
}

bool LazyPropagationSegmentTree::isInvalidIndex(int index)
{
	return index < leftmost || rightmost < index;
}

bool LazyPropagationSegmentTree::isInvalidType(int type)
{
	return type < 1 || 6 < type;
}

void LazyPropagationSegmentTree::initializeMin(long long *array,int node,int start,int end)
{
	if(start == end)
		tree[node] = array[start];
	else
	{
		initializeMin(array,node << 1,start,(start + end) >> 1);
		initializeMin(array,(node << 1) | 1,((start + end) >> 1) + 1,end);
		tree[node] = tree[node << 1] < tree[(node << 1) | 1] ? tree[node << 1] : tree[(node << 1) | 1];
	}
}

void LazyPropagationSegmentTree::initializeMax(long long *array,int node,int start,int end)
{
	if(start == end)
		tree[node] = array[start];
	else
	{
		initializeMax(array,node << 1,start,(start + end) >> 1);
		initializeMax(array,(node << 1) | 1,((start + end) >> 1) + 1,end);
		tree[node] = tree[node << 1] < tree[(node << 1) | 1] ? tree[(node << 1) | 1] : tree[node << 1];
	}
}

void LazyPropagationSegmentTree::initializeSum(long long *array,int node,int start,int end)
{
	if(start == end)
		tree[node] = array[start];
	else
	{
		initializeSum(array,node << 1,start,(start + end) >> 1);
		initializeSum(array,(node << 1) | 1,((start + end) >> 1) + 1,end);
		tree[node] = tree[node << 1] + tree[(node << 1) | 1];
	}
}

void LazyPropagationSegmentTree::initializeAnd(long long *array,int node,int start,int end)
{
	if(start == end)
	{
		tree[node] = array[start];
		lazy[node] = 9223372036854775807;
	}
	else
	{
		initializeAnd(array,node << 1,start,(start + end) >> 1);
		initializeAnd(array,(node << 1) | 1,((start + end) >> 1) + 1,end);
		tree[node] = tree[node << 1] & tree[(node << 1) | 1];
		lazy[node] = 9223372036854775807;
	}
}

void LazyPropagationSegmentTree::initializeOr(long long *array,int node,int start,int end)
{
	if(start == end)
		tree[node] = array[start];
	else
	{
		initializeOr(array,node << 1,start,(start + end) >> 1);
		initializeOr(array,(node << 1) | 1,((start + end) >> 1) + 1,end);
		tree[node] = tree[node << 1] | tree[(node << 1) | 1];
	}
}

void LazyPropagationSegmentTree::initializeXor(long long *array,int node,int start,int end)
{
	if(start == end)
		tree[node] = array[start];
	else
	{
		initializeXor(array,node << 1,start,(start + end) >> 1);
		initializeXor(array,(node << 1) | 1,((start + end) >> 1) + 1,end);
		tree[node] = tree[node << 1] ^ tree[(node << 1) | 1];
	}
}

long long LazyPropagationSegmentTree::getMin(int node,int start,int end,int left,int right)
{
	updateMinLazy(node,start,end);

	if(end < left || right < start)
		return (long long)9223372036854775807;
	else if(left <= start && end <= right)
		return tree[node];
	else
	{
		long long leftValue = getMin(node << 1,start,(start + end) >> 1,left,right), rightValue = getMin((node << 1) | 1,((start + end) >> 1) + 1,end,left,right);

		return leftValue < rightValue ? leftValue : rightValue;
	}
}

long long LazyPropagationSegmentTree::getMax(int node,int start,int end,int left,int right)
{
	updateMaxLazy(node,start,end);

	if(end < left || right < start)
		return (long long)-9223372036854775808;
	else if(left <= start && end <= right)
		return tree[node];
	else
	{
		long long leftValue = getMax(node << 1,start,(start + end) >> 1,left,right), rightValue = getMax((node << 1) | 1,((start + end) >> 1) + 1,end,left,right);

		return leftValue < rightValue ? rightValue : leftValue;
	}
}

long long LazyPropagationSegmentTree::getSum(int node,int start,int end,int left,int right)
{
	updateSumLazy(node,start,end);

	if(left > end || right < start)
		return 0;
	else if(left <= start && end <= right)
		return tree[node];
	else
		return getSum(node << 1,start,(start + end) >> 1,left,right) + getSum((node << 1) | 1,((start + end) >> 1) + 1,end,left,right);
}

long long LazyPropagationSegmentTree::getAnd(int node,int start,int end,int left,int right)
{
	updateAndLazy(node,start,end);

	if(left > end || right < start)
		return 9223372036854775807;
	else if(left <= start && end <= right)
		return tree[node];
	else
		return getAnd(node << 1,start,(start + end) >> 1,left,right) & getAnd((node << 1) | 1,((start + end) >> 1) + 1,end,left,right);
}

long long LazyPropagationSegmentTree::getOr(int node,int start,int end,int left,int right)
{
	updateOrLazy(node,start,end);

	if(left > end || right < start)
		return 0;
	else if(left <= start && end <= right)
		return tree[node];
	else
		return getOr(node << 1,start,(start + end) >> 1,left,right) | getOr((node << 1) | 1,((start + end) >> 1) + 1,end,left,right);
}

long long LazyPropagationSegmentTree::getXor(int node,int start,int end,int left,int right)
{
	updateXorLazy(node,start,end);

	if(left > end || right < start)
		return 0;
	else if(left <= start && end <= right)
		return tree[node];
	else
		return getXor(node << 1,start,(start + end) >> 1,left,right) ^ getXor((node << 1) | 1,((start + end) >> 1) + 1,end,left,right);
}

void LazyPropagationSegmentTree::updateMin(int node,int start,int end,int left,int right,long long diff)
{
	updateMinLazy(node,start,end);

	if(right < start || end < left)
		return;
	if(left <= start && end <= right)
	{
		tree[node] += diff;

		if(start != end)
		{
			lazy[node << 1] += diff;
			lazy[(node << 1) | 1] += diff;
		}

		return;
	}

	updateMin(node << 1,start,(start + end) >> 1,left,right,diff);
	updateMin((node << 1) | 1,((start + end) >> 1) + 1,end,left,right,diff);
	tree[node] = tree[node << 1] < tree[(node << 1) | 1] ? tree[node << 1] : tree[(node << 1) | 1];
}

void LazyPropagationSegmentTree::updateMax(int node,int start,int end,int left,int right,long long diff)
{
	updateMaxLazy(node,start,end);

	if(right < start || end < left)
		return;
	if(left <= start && end <= right)
	{
		tree[node] += diff;

		if(start != end)
		{
			lazy[node << 1] += diff;
			lazy[(node << 1) | 1] += diff;
		}

		return;
	}

	updateMax(node << 1,start,(start + end) >> 1,left,right,diff);
	updateMax((node << 1) | 1,((start + end) >> 1) + 1,end,left,right,diff);
	tree[node] = tree[node << 1] < tree[(node << 1) | 1] ? tree[(node << 1) | 1] : tree[node << 1];
}

void LazyPropagationSegmentTree::updateSum(int node,int start,int end,int left,int right,long long diff)
{
	updateSumLazy(node,start,end);

	if(right < start || end < left)
		return;
	if(left <= start && end <= right)
	{
		tree[node] += diff * (end - start + 1);

		if(start != end)
		{
			lazy[node << 1] += diff;
			lazy[(node << 1) | 1] += diff;
		}

		return;
	}

	updateSum(node << 1,start,(start + end) >> 1,left,right,diff);
	updateSum((node << 1) | 1,((start + end) >> 1) + 1,end,left,right,diff);
	tree[node] = tree[node << 1] + tree[(node << 1) | 1];
}

void LazyPropagationSegmentTree::updateAnd(int node,int start,int end,int left,int right,long long diff)
{
	updateAndLazy(node,start,end);

	if(right < start || end < left)
		return;
	if(left <= start && end <= right)
	{
		tree[node] &= diff;

		if(start != end)
		{
			lazy[node << 1] = diff;
			lazy[(node << 1) | 1] = diff;
		}

		return;
	}

	updateAnd(node << 1,start,(start + end) >> 1,left,right,diff);
	updateAnd((node << 1) | 1,((start + end) >> 1) + 1,end,left,right,diff);
	tree[node] = tree[node << 1] & tree[(node << 1) | 1];
}

void LazyPropagationSegmentTree::updateOr(int node,int start,int end,int left,int right,long long diff)
{
	updateOrLazy(node,start,end);

	if(right < start || end < left)
		return;
	if(left <= start && end <= right)
	{
		tree[node] |= diff;

		if(start != end)
		{
			lazy[node << 1] |= diff;
			lazy[(node << 1) | 1] |= diff;
		}

		return;
	}

	updateOr(node << 1,start,(start + end) >> 1,left,right,diff);
	updateOr((node << 1) | 1,((start + end) >> 1) + 1,end,left,right,diff);
	tree[node] = tree[node << 1] | tree[(node << 1) | 1];
}

void LazyPropagationSegmentTree::updateXor(int node,int start,int end,int left,int right,long long diff)
{
	updateXorLazy(node,start,end);

	if(right < start || end < left)
		return;
	if(left <= start && end <= right)
	{
		tree[node] ^= diff;

		if(start != end)
		{
			lazy[node << 1] ^= diff;
			lazy[(node << 1) | 1] ^= diff;
		}

		return;
	}

	updateXor(node << 1,start,(start + end) >> 1,left,right,diff);
	updateXor((node << 1) | 1,((start + end) >> 1) + 1,end,left,right,diff);
	tree[node] = tree[node << 1] ^ tree[(node << 1) | 1];
}

void LazyPropagationSegmentTree::updateMinLazy(int node,int start,int end)
{
	if(lazy[node] != 0)
	{
		tree[node] += lazy[node];
		if(start != end)
		{
			lazy[node << 1] += lazy[node];
			lazy[(node << 1) | 1] += lazy[node];
		}
		lazy[node] = 0;
	}
}

void LazyPropagationSegmentTree::updateMaxLazy(int node,int start,int end)
{
	if(lazy[node] != 0)
	{
		tree[node] += lazy[node];
		if(start != end)
		{
			lazy[node << 1] += lazy[node];
			lazy[(node << 1) | 1] += lazy[node];
		}
		lazy[node] = 0;
	}
}

void LazyPropagationSegmentTree::updateSumLazy(int node,int start,int end)
{
	if(lazy[node] != 0)
	{
		tree[node] += lazy[node] * (end - start + 1);
		if(start != end)
		{
			lazy[node << 1] += lazy[node];
			lazy[(node << 1) | 1] += lazy[node];
		}
		lazy[node] = 0;
	}
}

void LazyPropagationSegmentTree::updateAndLazy(int node,int start,int end)
{
	if(lazy[node] != 9223372036854775807)
	{
		tree[node] &= lazy[node];
		if(start != end)
		{
			lazy[node << 1] &= lazy[node];
			lazy[(node << 1) | 1] &= lazy[node];
		}
		lazy[node] = 9223372036854775807;
	}
}

void LazyPropagationSegmentTree::updateOrLazy(int node,int start,int end)
{
	if(lazy[node] != 0)
	{
		tree[node] |= lazy[node];
		if(start != end)
		{
			lazy[node << 1] |= lazy[node];
			lazy[(node << 1) | 1] |= lazy[node];
		}
		lazy[node] = 0;
	}
}

void LazyPropagationSegmentTree::updateXorLazy(int node,int start,int end)
{
	if(lazy[node] != 0)
	{
		tree[node] ^= lazy[node];
		if(start != end)
		{
			lazy[node << 1] ^= lazy[node];
			lazy[(node << 1) | 1] ^= lazy[node];
		}
		lazy[node] = 0;
	}
}