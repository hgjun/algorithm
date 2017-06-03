#include <stdio.h>

#define FOR(i, n)                        for (i = 1; i <= (n); i++)
#define FORFROM(i, m, n)                 for (i = (m); i <= (n); i++)
#define FORDEC(i, m, n)                  for (i = (m); i >= (n); i--)

#define MAX(x, y)                        ((x) >= (y) ? (x) : (y))
#define MIN(x, y)                        ((x) <= (y) ? (x) : (y))

#define MAX_SIZE 101

int radix = 6;
int size;

typedef struct radixSix_t {
	int twoCount;
	int threeCount;
} RadixSix;

typedef struct radixSixSet_t {
	RadixSix num[1200];
	int setSize;
} RadixSixSet;
 

RadixSix    mat[MAX_SIZE][MAX_SIZE];
RadixSixSet res[MAX_SIZE][MAX_SIZE];

/*
int getZeroCount(RadixSix v)
{
	return MIN(v.twoCount, v.threeCount);
}
*/

void addData(RadixSix *dest, RadixSix *source1, RadixSix *source2)
{
	dest->twoCount   = source1->twoCount   + source2->twoCount;
	dest->threeCount = source1->threeCount + source2->threeCount;
}


int getIndexByThreeCount(RadixSixSet *set, int threeCount)
{
	int setSize = set->setSize;

	int i;
	FOR(i, setSize) {
		if (set->num[i].threeCount == threeCount) {
			return i;
		}
	}
	// if not exist return set size + 1 
	return setSize + 1;
}


void setCount(RadixSix *p, unsigned int num)
{
	unsigned int twoCount = 0;
	unsigned int threeCount = 0;
	
	unsigned int isTwoCheckEnd = 0;
	unsigned int isThreeCheckEnd = 0;

	while (num) {		
		if ( (num % 2) == 0) {
			twoCount++;
			num /= 2;
		}
		else {
			isTwoCheckEnd = 1;
		}
		
		if ( (num % 3) == 0) {
			threeCount++;
			num /= 3;
		}
		else {
			isThreeCheckEnd = 1;
		}
		
		if (isTwoCheckEnd && isThreeCheckEnd) {
			p->twoCount = twoCount;
			p->threeCount = threeCount;
			return;
		}
	}
}

int main(void) {

	//freopen("roomExit.txt", "r", stdin);
	setbuf(stdout, NULL);

	int T;
	int test_case;
	int i, j, k;
	unsigned int num;
	
	scanf("%d", &T);
	for(test_case = 1; test_case <= T; test_case++) {
 		scanf("%d", &size);

		FOR(i, size) {
			FOR(j, size) {
				scanf("%d", &num);
				setCount(&mat[i][j], num);
				res[i][j].setSize =0;
			}
		}
		
		int initSize = 1;
		
		res[1][1].setSize = initSize;
		res[1][1].num[initSize] = mat[1][1];
		
		
		FORFROM(i, 2, size) {
			res[i][1].setSize = initSize;
			addData(&res[i][1].num[initSize], &res[i - 1][1].num[initSize], &mat[i][1]);

		}
		FORFROM(j, 2, size) {
			res[1][j].setSize = initSize;
			addData(&res[1][j].num[initSize], &res[1][j - 1].num[initSize], &mat[1][j]);
		}
		
		
		RadixSixSet *pUp, *pLeft, *pCurrent;
		FORFROM(i, 2, size) {
			FORFROM(j, 2, size) {
				pCurrent = &res[i][j];

				// Step 1. Current & Up
				// mat(i,j) + Up.num[1 ~ setSize] ===> mat(i,j).num[  ]
				pUp = &res[i-1][j];
				pCurrent->setSize = 0;
				FOR(k, pUp->setSize) {
					pCurrent->setSize++;
					addData(&pCurrent->num[pCurrent->setSize], &pUp->num[k], &mat[i][j]);
				}
				
				// Step 2. Current & Left
				// mat(i,j) + Left.num[1 ~ setSize] ===> mat(i,j).num[  ]
				pLeft = &res[i][j-1];
				int setIdx;
				FOR(k, pLeft->setSize) {
					setIdx = getIndexByThreeCount(pCurrent, pLeft->num[k].threeCount + mat[i][j].threeCount);
					// new threeCount number (not in the set 'pUp')
					if (setIdx == pCurrent->setSize + 1) {				
						pCurrent->setSize++;
						addData(&pCurrent->num[setIdx], &pLeft->num[k], &mat[i][j]); 
					}
					// if exist in the set (processed in the step 1)
					else {
						int twoCount = pLeft->num[k].twoCount + mat[i][j].twoCount;
						if (twoCount > pCurrent->num[setIdx].twoCount) {
							pCurrent->num[setIdx].twoCount = twoCount; // update with greator twoCount
						}
					}
				}
				
			}
		}
	
	
	
		RadixSixSet *lastElem = &res[size][size];		
		int zeroCount = 0;

		FOR(i, lastElem->setSize) {
			//zeroCount = MAX(zeroCount, getZeroCount(lastElem->num[i]));
			
			// 함수 안쓰면 2.233 -> 2.211 줄음 
			zeroCount = MAX(zeroCount, MIN(lastElem->num[i].twoCount, lastElem->num[i].threeCount));	
		}
		printf("Case #%d\n%d\n", test_case, zeroCount);
        
	}

	return 0;
}
