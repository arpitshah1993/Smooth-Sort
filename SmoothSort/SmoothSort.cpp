#include "SmoothSort.h"
#include<iostream>
//upgrade the pair of lenonardo number
#define UP(IA,IB) temp = IA; IA += IB + 1; IB = temp;
//downsize the pair of lenonardo number
#define DOWN(IA,IB) temp = IB; IB = IA - IB - 1; IA = temp;

//constructor
SmoothSort::SmoothSort()
{
}

//destructor
SmoothSort::~SmoothSort()
{
}

// check whether number a and b are sorted
bool SmoothSort::IsSorted(int a, int b)
{
	countComparison++;
	return a < b ? true : false;
}

//It is applied to an element without larger sons is a 
//skip.If it applied to an element m(r1) that is exceeded 
//by its largest son m(r2), it consists of a swap of these two values, 
//followed by an application of sift to m(r2).
void SmoothSort::Sift()
{
	int r0, r2, temp;
	int t;
	r0 = root1;
	t = A[r0];

	while (baseStretch1 >= 3)
	{
		r2 = root1 - baseStretch1 + companionStretch1;

		if (!IsSorted(A[root1 - 1], A[r2]))
		{
			r2 = root1 - 1;
			DOWN(baseStretch1, companionStretch1);
		}

		if (IsSorted(A[r2], t))
		{
			baseStretch1 = 1;
		}
		else
		{
			A[root1] = A[r2];
			root1 = r2;
			DOWN(baseStretch1, companionStretch1);
		}
	}

	if (root1 - r0)
		A[root1] = t;
}

//print the full heap
void SmoothSort::printInput()
{
	std::cout << "[ ";
    for (int var : A)
	{
		std::cout << var << " ";
	}
	std::cout << "] \n";
}

//print the total number of comparison and reset the count variable
void SmoothSort::printComparison()
{
	std::cout << "The total number of comparisons among elements in A performed :";
	std::cout << countComparison;
	std::cout << "\n";
	//reset the count after printing it
	countComparison = 0;
}

//print the output in which every 20th element of vector has been printed
void SmoothSort::printOutput()
{
	std::cout << "\nA shortened listing of element of A :\n ";
	std::cout << "[ ";
	for (int i = 0; i < A.size(); i++)
	{
		if (i % 20 == 0)
		{
			std::cout << A[i] << " ";
		}
	}
	std::cout << "] ";
	std::cout << "\n";
}

//push the element in the heap
void SmoothSort::push(int i)
{
	A.push_back(i);
}

//It is used to make dubious stretch trusty including its root in the sequence of ascending roots
void SmoothSort::Trinkle()
{
	int p1, r2, r3, r0, temp;
	int t;
	p1 = leoHeapPlan;
	baseStretch1 = H1Size;
	companionStretch1 = H2Size;
	r0 = root1;
	t = A[r0];

	while (p1 > 0)
	{
		while ((p1 & 1) == 0)
		{
			p1 >>= 1;
			UP(baseStretch1, companionStretch1)
		}

		r3 = root1 - baseStretch1;

		if ((p1 == 1) || IsSorted(A[r3], t))
		{
			p1 = 0;
		}
		else
		{
			--p1;

			if (baseStretch1 == 1)
			{
				A[root1] = A[r3];
				root1 = r3;
			}
			else
			{
				if (baseStretch1 >= 3)
				{
					r2 = root1 - baseStretch1 + companionStretch1;

					if (!IsSorted(A[root1 - 1], A[r2]))
					{
						r2 = root1 - 1;
						DOWN(baseStretch1, companionStretch1);
						p1 <<= 1;
					}
					if (IsSorted(A[r2], A[r3]))
					{
						A[root1] = A[r3]; root1 = r3;
					}
					else
					{
						A[root1] = A[r2];
						root1 = r2;
						DOWN(baseStretch1, companionStretch1);
						p1 = 0;
					}
				}
			}
		}
	}

	if (r0 - root1)
		A[root1] = t;

	Sift();
}

//semitrinkle is used to take care of the two subtrees, it exchanges their
//roots if necessary and use trinkle to restore the root - sorted forest.
void SmoothSort::SemiTrinkle()
{
	int T;
	root1 = rightMostElementOfUnsortedList - H2Size;

	if (!IsSorted(A[root1], A[rightMostElementOfUnsortedList]))
	{
		T = A[rightMostElementOfUnsortedList];
		A[rightMostElementOfUnsortedList] = A[root1];
		A[root1] = T;
		Trinkle();
	}
}

//sorting an array using smooth sort using two case
void SmoothSort::SmoothSorting()
{
	const int N = A.size();
	int temp;
	unsortedListLength = 1;
	rightMostElementOfUnsortedList = 0;
	leoHeapPlan = 1;
	H1Size = 1;
	H2Size = 1;

	while (unsortedListLength < N)
	{
		root1 = rightMostElementOfUnsortedList;
		//case 1:standard concatenation ends on a dubious stretch 
		//which must be made trusty before it can be combined with
		//the preceding stretch and the following element into a new dubious rightmost stretch
		if ((leoHeapPlan & 7) == 3)
		{
			baseStretch1 = H1Size;
			companionStretch1 = H2Size;
			//applying sift operation at rightMostElementOfUnsortedList;
			Sift();
			leoHeapPlan = (leoHeapPlan + 1) >> 2;
			UP(H1Size, H2Size);
			UP(H1Size, H2Size);
		}

		//standard concatenation ends on a dubious stretch 
		//which in this step becomes the last
		else if ((leoHeapPlan & 3) == 1)
		{
			if (unsortedListLength + H2Size< N)
			{
				baseStretch1 = H1Size;
				companionStretch1 = H2Size;
				Sift();
			}
			else
			{
				Trinkle();
			}

			DOWN(H1Size, H2Size);
			leoHeapPlan <<= 1;

			while (H1Size > 1)
			{
				DOWN(H1Size, H2Size);
				leoHeapPlan <<= 1;
			}

			leoHeapPlan++;
		}

		unsortedListLength++;
		rightMostElementOfUnsortedList++;
	}

	root1 = rightMostElementOfUnsortedList;
	Trinkle();

	while (unsortedListLength > 1)
	{
		--unsortedListLength;

		if (H1Size == 1)
		{
			rightMostElementOfUnsortedList--;
			leoHeapPlan--;

			while ((leoHeapPlan & 1) == 0)
			{
				leoHeapPlan >>= 1;
				UP(H1Size, H2Size);
			}
		}
		else
		{
			if (H1Size >= 3) {
				leoHeapPlan--;
				rightMostElementOfUnsortedList = rightMostElementOfUnsortedList - H1Size + H2Size;
				if (leoHeapPlan > 0)
					SemiTrinkle();

				DOWN(H1Size, H2Size);
				leoHeapPlan = (leoHeapPlan << 1) + 1;
				rightMostElementOfUnsortedList = rightMostElementOfUnsortedList + H2Size;
				SemiTrinkle();
				DOWN(H1Size, H2Size);
				leoHeapPlan = (leoHeapPlan << 1) + 1;
			}
		}
	}
}
