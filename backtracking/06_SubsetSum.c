#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "macrofunctions.h"


#define ARRAYSIZE(a) (sizeof(a))/(sizeof(a[0]))

static int total_nodes;
// prints subset found
void printSubset(int A[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%*d", 5, A[i]);
	}

	printf("\n");
}

// inputs
// s            - set vector
// t            - tuplet vector
// s_size       - set size
// t_size       - tuplet size so far
// sum          - sum so far
// ite          - nodes count
// target_sum   - sum to be found
void subset_sum(int s[], int t[],
	int s_size, int t_size,
	int sum, int ite,
	int const target_sum)
{
	total_nodes++;
	if (target_sum == sum)
	{
		// We found subset
		printSubset(t, t_size);
		// Exclude previously added item and consider next candidate
		subset_sum(s, t, s_size, t_size - 1, sum - s[ite], ite + 1, target_sum);
		return;
	}
	else
	{
		// generate nodes along the breadth
		for (int i = ite; i < s_size; i++)
		{
			t[t_size] = s[i];
			// consider next level node (along depth)
			subset_sum(s, t, s_size, t_size + 1, sum + s[i], i + 1, target_sum);
		}
	}
}

// Wrapper to print subsets that sum to target_sum
// input is weights vector and target_sum
void generateSubsets(int s[], int size, int target_sum)
{
	int *tuplet_vector = (int *)malloc(size * sizeof(int));

	subset_sum(s, tuplet_vector, size, 0, 0, 0, target_sum);

	free(tuplet_vector);
}

// qsort compare function
int comparator(const void *pLhs, const void *pRhs)
{
	int *lhs = (int *)pLhs;
	int *rhs = (int *)pRhs;

	return *lhs > *rhs;
}


// inputs
// s            - set vector
// t            - tuplet vector
// s_size       - set size
// t_size       - tuplet size so far
// sum          - sum so far
// ite          - nodes count
// target_sum   - sum to be found
void opt_subset_sum(int s[], int t[],
	int s_size, int t_size,
	int sum, int ite,
	int const target_sum)
{
	total_nodes++;

	if (target_sum == sum)
	{
		// We found sum
		printSubset(t, t_size);

		// constraint check
		if (ite + 1 < s_size && sum - s[ite] + s[ite + 1] <= target_sum)
		{
			// Exclude previous added item and consider next candidate
			opt_subset_sum(s, t, s_size, t_size - 1, sum - s[ite], ite + 1, target_sum);
		}
		return;
	}
	else
	{
		// constraint check
		if (ite < s_size && sum + s[ite] <= target_sum)
		{
			// generate nodes along the breadth
			for (int i = ite; i < s_size; i++)
			{
				t[t_size] = s[i];

				if (sum + s[i] <= target_sum)
				{
					// consider next level node (along depth)
					opt_subset_sum(s, t, s_size, t_size + 1, sum + s[i], i + 1, target_sum);
				}
			}
		}
	}
}

void optGenerateSubsets(int s[], int size, int target_sum)
{
	int *tuplet_vector = (int *)malloc(size * sizeof(int));

	int total = 0;

	// sort the set
	qsort(s, size, sizeof(int), &comparator);

	for (int i = 0; i < size; i++)
	{
		total += s[i];
	}

	if (s[0] <= target_sum && total >= target_sum)
	{

		opt_subset_sum(s, tuplet_vector, size, 0, 0, 0, target_sum);

	}

	free(tuplet_vector);
}

int main()
{
	int weights[] = { 10, 7, 5, 18, 12, 20, 15 };
	int size = ARRAYSIZE(weights);
	int targetSum = 35;
	total_nodes = 0;
	printf("Find subset sum = %d\n", targetSum);
	generateSubsets(weights, size, 35);
	printf("Nodes generated %d\n\n", total_nodes);

	printf("Branch and bound:\n");
	total_nodes = 0;
	optGenerateSubsets(weights, size, targetSum);
	printf("Nodes generated %d\n", total_nodes);
	system("pause");
	return 0;
}
