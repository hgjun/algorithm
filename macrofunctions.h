#pragma once

#define PRT               printf
#define PRTD(n)           printf("%-3d", (n))
#define PRTLN             printf("\n");

#define FOR(i, n)         for (i = 1; i <= (n); i++)
#define FORFROM(i, m, n)  for (i = (m); i <= (n); i++)
#define FORDEC(i, m, n)   for (i = (m); i >= (n); i--)

#define MIN(x, y)         ((x) <= (y) ? (x) : (y))
#define MAX(x, y)         ((x) >= (y) ? (x) : (y))

#define SWAP(x, y)        \
		do {\
			int tmp_ = (x);\
			(x) = (y);\
			(y) = tmp_;\
		} while (0)

#define FILL_ARRAY(arr, size, v) \
		do {\
			int i_;\
			for (i_ = size; i_ >= 0; i_--)\
				arr[i_] = (v);\
		} while (0)

#define COPY_ARRAY(dest, d_begin, source, s_begin, s_end) \
		do {\
			int i_, j_ = (d_begin);\
			for (i_ = (s_begin); i_ <= (s_end); i_++)\
				dest[j_++] = source[i_];\
		} while (0)

#define FILL_MATRIX(mat, row, col, v) \
		do {\
			int i_, j_;\
			for (i_ = (row); i_ >= 0; i_--)\
				for (j_ = (col); j_ >= 0; j_--)\
					mat[i_][j_] = (v);\
		} while (0)

#define COPY_MATRIX(dest, source, row, col) \
		do {\
			int i_, j_;\
			for (i_ = (row); i_ >= 0; i_--)\
				for (j_ = (col); j_ >= 0; j_--)\
					dest[i_][j_] = source[i_][j_];\
		} while (0)

#define TR_MATRIX(dest, source, row, col) \
		do {\
			int i_, j_;\
			for (i_ = (row); i_ >= 0; i_--)\
				for (j_ = (col); j_ >= 0; j_--)\
					dest[j_][i_] = source[i_][j_];\
		} while (0)
