#include<cstdio>
#include<vector>
class SmoothSort
{
public:
	//H1size=size of Heap1 and H2size=size of Heap2, Heap1size>=Heap2size
	int unsortedListLength, rightMostElementOfUnsortedList, leoHeapPlan, H1Size, H2Size, root1, baseStretch1, companionStretch1, countComparison = 0;
	std::vector<int> A;
	SmoothSort();
	~SmoothSort();
	void push(int);
	void printInput();
	void printOutput();
	bool IsSorted(int, int);
	void Sift();
	void Trinkle();
	void SemiTrinkle();
	void printComparison();
	void SmoothSorting();
};

