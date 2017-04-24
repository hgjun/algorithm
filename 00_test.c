#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <conio.h>

typedef struct links_t {
	char name[1024];
	int *link;
	int  linkSize;
} Links;


int main(void)
{
	int i, j;
	printf("%s %d %s\n", __FUNCTION__, __LINE__, __FILE__);
	/*
	FILE *fp = fopen("input.txt", "r");
	FILE *fw = fopwn("output.txt", "w");

	char buf1[1024], buf2[1024], *p;
	while (!feof(fp))
	int x;

	fgets(buf1, 1024, fp);
	fscanf(fp, "%*s %s %d", buf1, &x);
	buf1[ strlen(buf1) - 1 ] = '\0';
	strcpy(buf2, buf1);
	for (p = strtok(buf1, " "); p; p = strtok(NULL, " ")) {
	int n = atoi(p);
	}
	fprintf(fp, "%d %s", x, buf2);
	rewind(fp);
	fclose(fp);
	fclose(fw);
	*/

	// memory allocation
	int size = 100;
	Links links[101];

	for (i = 1; i <= size; i++) {
		links[i].link = (int*)malloc(sizeof(int) * size);
	}

	int **mat;
	mat = (int**)malloc(sizeof(int*) * (size + 1));
	for (i = 1; i <= size; i++) {
		mat[i] = (int*)malloc(sizeof(int) * (size + 1));
	}

	for (i = 1; i <= size; i++) {
		free(links[i].link);
		free(mat[i]);
	}
	free(mat);

	// time check
	clock_t t1 = clock();
	double diff = (double)(clock() - t1) * CLOCKS_PER_SEC;

	// swap
	int a = 3;
	int b = 7;

	printf("a=%d, b=%d\n", a, b);
	a += b;
	b = a - b;
	a -= b;
	printf("a=%d, b=%d\n", a, b);

	// arry iteration with pointer
	int c[10];
	int *p;

	for (p = (&c)[0]; p < (&c)[1]; p++) *p = 0;
	for (p = c; p < &c[10]; p++) *p = 1;
	for (p = c; p < c + 10; p++) *p = 2;
	for (i = 0; i < 10; i++) {
		printf("%-3d", c[i]);
	}

	/*printf("\n==%d", c[10]);
	printf("\n%d", (&c)[1]);
	printf("\n%d", (&c)[0]);
	printf("\n%d", &c[1] - c);
	printf("\n%d", (&c)[1] - c);
	printf("\n"); printf("\n");*/

	int d[10][10];
	int(*pRow)[10];

	for (p = &d[0][0]; p < (&d[10])[0]; p++) *p = 0;
	for (p = &d[0][0]; p <= &d[9][9]; p++) *p = 1;

	for (pRow = d; pRow < d + 4; pRow++) {
		for (p = pRow[0]; p < pRow[0] + 5; p++) {
			*p = 3;
		}
	}
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			printf("%-3d", d[i][j]);
		}
		printf("\n");
	}

	// char table
	static char *table = "ABCDE";
	char letter = table[1];
	printf("\n\nchar=%c\n", letter);


	char values[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char find = 'A';

	const char *ptr = strchr(values, find);
	if (ptr) {
		int index = ptr - values;
		printf("Found idx %d\n", index);
		// do something
	}

	system("pause");
	return 0;
}