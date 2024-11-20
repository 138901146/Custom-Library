//
// Created by 박우현 on 2024-11-20.
//

#include "SegmentTree.h"

SegmentTree::SegmentTree() { }

SegmentTree::~SegmentTree()
{
	if(tree != nullptr)
	{
		delete tree;
	}

	tree = nullptr;
}

bool SegmentTree::initialize(int type,int size,long long *array)
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
	}

	return true;
}

long long SegmentTree::get(int left,int right)
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
		default:
			return -1;	// TODO: 만약 결과값이 진짜 -1인 경우 문제 발생 -> 추후 학습 후 ERROR CODE 생성 또는 throw 등으로 변경 요망.
	}

	return value;
}

bool SegmentTree::update(int index,long long value)
{
	if(isInvalidIndex(index))
	{
		return false;
	}

	switch(getType())
	{
		case MIN:
			updateMin(1,leftmost,rightmost,index,value);
			break;
		case MAX:
			updateMax(1,leftmost,rightmost,index,value);
			break;
		case SUM:
			updateSum(1,leftmost,rightmost,index,value);
			break;
		default:
			return false;
	}

	return true;
}

int SegmentTree::getType()
{
	return type;
}

int SegmentTree::getTreeSize()
{
	return treeSize;
}

bool SegmentTree::isInvalidIndex(int index)
{
	return index < leftmost || rightmost < index;
}

bool SegmentTree::isInvalidType(int type)
{
	return type < 1 || 3 < type;
}

void SegmentTree::initializeMin(long long *array,int node,int start,int end)
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

void SegmentTree::initializeMax(long long *array,int node,int start,int end)
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

void SegmentTree::initializeSum(long long *array,int node,int start,int end)
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

long long SegmentTree::getMin(int node,int start,int end,int left,int right)
{
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

long long SegmentTree::getMax(int node,int start,int end,int left,int right)
{
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

long long SegmentTree::getSum(int node,int start,int end,int left,int right)
{
	if(left > end || right < start)
		return 0;
	else if(left <= start && end <= right)
		return tree[node];
	else
		return getSum(node << 1,start,(start + end) >> 1,left,right) + getSum((node << 1) | 1,((start + end) >> 1) + 1,end,left,right);
}

void SegmentTree::updateMin(int node,int start,int end,int index,long long value)
{
	if(index < start || end < index)
		return;
	else if(start == end)
	{
		tree[node] = value;
		return;
	}
	else
	{
		updateMin(node << 1,start,(start + end) >> 1,index,value);
		updateMin((node << 1) | 1,((start + end) >> 1) + 1,end,index,value);
		tree[node] = tree[node << 1] < tree[(node << 1) | 1] ? tree[node << 1] : tree[(node << 1) | 1];
	}
}

void SegmentTree::updateMax(int node,int start,int end,int index,long long value)
{
	if(index < start || end < index)
		return;
	else if(start == end)
	{
		tree[node] = value;
		return;
	}
	else
	{
		updateMax(node << 1,start,(start + end) >> 1,index,value);
		updateMax((node << 1) | 1,((start + end) >> 1) + 1,end,index,value);
		tree[node] = tree[node << 1] < tree[(node << 1) | 1] ? tree[(node << 1) | 1] : tree[node << 1];
	}
}

void SegmentTree::updateSum(int node,int start,int end,int index,long long value)
{
	if(index < start || end < index)
		return;
	else if(start == end)
	{
		tree[node] = value;
		return;
	}
	else
	{
		updateSum(node << 1,start,(start + end) >> 1,index,value);
		updateSum((node << 1) | 1,((start + end) >> 1) + 1,end,index,value);
		tree[node] = tree[node << 1] + tree[(node << 1) | 1];
	}
}
