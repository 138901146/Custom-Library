//
// Created by 박우현 on 2024-11-20.
//

#ifndef C___LAZYPROPAGATIONSEGMENTTREE_H
#define C___LAZYPROPAGATIONSEGMENTTREE_H


class LazyPropagationSegmentTree
{
public:
	LazyPropagationSegmentTree();
	~LazyPropagationSegmentTree();

	bool initialize(int type,int size,long long *array);
	long long get(int left,int right);
	bool update(int left,int right,long long diff);
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
	long long *lazy = nullptr;

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
	void updateMin(int node,int start,int end,int left,int right,long long diff);
	void updateMax(int node,int start,int end,int left,int right,long long diff);
	void updateSum(int node,int start,int end,int left,int right,long long diff);
	void updateAnd(int node,int start,int end,int left,int right,long long diff);
	void updateOr(int node,int start,int end,int left,int right,long long diff);
	void updateXor(int node,int start,int end,int left,int right,long long diff);
	void updateMinLazy(int node,int start,int end);
	void updateMaxLazy(int node,int start,int end);
	void updateSumLazy(int node,int start,int end);
	void updateAndLazy(int node,int start,int end);
	void updateOrLazy(int node,int start,int end);
	void updateXorLazy(int node,int start,int end);

	bool isInvalidIndex(int index);
	bool isInvalidType(int type);
};


#endif //C___LAZYPROPAGATIONSEGMENTTREE_H
