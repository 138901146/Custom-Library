//
// Created by 박우현 on 2024-11-20.
//

#ifndef CUSTOM_LIBRARY_SEGMENTTREE_H
#define CUSTOM_LIBRARY_SEGMENTTREE_H


class SegmentTree
{
public:
	SegmentTree();
	~SegmentTree();

	bool initialize(int type,int size,long long *array);
	long long get(int left,int right);
	bool update(int index,long long value);
	int getType();
	int getTreeSize();

	enum TYPE
	{
		UNDEFINED = 0,
		SUM = 1,
		MAX = 2,
		MIN = 3,
		AND = 4,
		OR = 5,
		XOR = 6,
	};

private:
	int type;
	int treeSize;
	int leftmost;
	int rightmost;
	long long *tree = nullptr;

	void initializeMin(long long *array,int node,int start,int end);
	void initializeMax(long long *array,int node,int start,int end);
	void initializeSum(long long *array,int node,int start,int end);
	void initializeAnd(long long *array,int node,int start,int end);
	void initializeOr(long long *array,int node,int start,int end);
	void initializeXor(long long *array,int node,int start,int end);
	long long getMin(int node,int start,int end,int left,int right);
	long long getMax(int node,int start,int end,int left,int right);
	long long getSum(int node,int start,int end,int left,int right);
	long long getAnd(int node,int start,int end,int left,int right);
	long long getOr(int node,int start,int end,int left,int right);
	long long getXor(int node,int start,int end,int left,int right);
	void updateMin(int node,int start,int end,int index,long long value);
	void updateMax(int node,int start,int end,int index,long long value);
	void updateSum(int node,int start,int end,int index,long long value);
	void updateAnd(int node,int start,int end,int index,long long value);
	void updateOr(int node,int start,int end,int index,long long value);
	void updateXor(int node,int start,int end,int index,long long value);

	bool isInvalidIndex(int index);
	bool isInvalidType(int type);
};


#endif //CUSTOM_LIBRARY_SEGMENTTREE_H
