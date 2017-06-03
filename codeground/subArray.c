#include <stdio.h>
#include <stdlib.h>

int main(void) {
   	/* �Ʒ� freopen �Լ��� sample_input.txt�� read only �������� ����, ǥ���Է�(Ű����) ��� sample_input.txt �� ���� �о���ڴٴ� �ǹ��� �ڵ��Դϴ�.
	   ���� ���� PC ���� �׽�Ʈ �� ����, �Է°��� sample_input.txt�� ������ �� freopen �Լ��� ����ϸ�
   	   �� �Ʒ����� scanf �Լ��� ����Ͽ� ǥ���Է� ��� sample_input.txt ���Ϸ� ���� �Է°��� �о� �� �� �ֽ��ϴ�.
   	   ����, ���� PC���� freopen �Լ��� ������� �ʰ� ǥ���Է��� ����Ͽ� �׽�Ʈ�ϼŵ� �����մϴ�.
	   ��, Codeground �ý��ۿ��� "�����ϱ�" �� ������ �ݵ�� freopen �Լ��� ����ų� �ּ�(//) ó�� �ϼž߸� �մϴ�. */
	freopen("sample.txt", "r", stdin);

	/* setbuf �Լ��� ������� ������, ������ ���α׷��� ���� '�ð� �ʰ�'�� ���� ���� �Ǿ��� ��,
	   printf�� ����� ������ ä������ �ʰ� '0��'�� �� ���� �ֽ��ϴ�.
	   �ð� �ʰ� ������ ����� ��� ������ �ް��� �ϽŴٸ� "setbuf(stdout, NULL);" �� ����Ͻñ� �ٶ��ϴ�. */
	
	setbuf(stdout, NULL);

	int T;
	int test_case;

	scanf("%d", &T);    
    
    int arrSize, threshold;
    int arr[100000];
	int minSize;
    int sumAll;
    int i, j;
    int sum, size;
    int isEnd = 0;
    int idx;
	for(test_case = 1; test_case <= T; test_case++) {
		// �� �κп��� �˰��� ���α׷��� �ۼ��Ͻʽÿ�. �⺻ ������ �ڵ带 ���� �Ǵ� �����ϰ� ������ �ڵ带 ����ϼŵ� �˴ϴ�.
        
        scanf("%d %d", &arrSize, &threshold);      
   
        minSize = 0;
        sum  = 0;
        size = 0;
        for (i = 1; i <= arrSize; i++) {
            scanf("%d", &arr[i]);
            if (isEnd == 0 && arr[i] >= threshold) {
            	sum     = arr[i];
            	minSize = 1;
            	isEnd   = 1;
			}
            if (isEnd == 0 && sum < threshold) {
            	sum += arr[i];
            	minSize++;
            	idx = i;
			}
        }
        arr[0] = 0;
        
        if (sum < threshold) {
        	minSize = 0;
		}      
		else if (minSize > 1 && minSize < arrSize) {
			printf("sum %d, minSize %d, idx %d\n", sum, minSize, idx);
			size = minSize;
			for (i = 1; i <= arrSize; i++) {
				printf("sum %d - arr[%d] = %d, size%d\n", sum, i, sum-arr[i], minSize - 1);
				sum -= arr[i];
				size--;
				while (sum < threshold) {
					if (idx == arrSize) {
						break;
					}
					sum += arr[++idx];
					size++;
					printf("+ %d (size%d)", arr[idx], size);
					
				}printf("\n");
				if (sum >= threshold && size < minSize) {
					minSize = size;
				}
				else if (sum < threshold && idx == arrSize) {
					break;
				}
			}
		}

		printf("arrSize %d, t %d, sum %d\n", arrSize, threshold, sum);     
		// �� �κп��� ������ ����Ͻʽÿ�.
		printf("#testcase%d\n%d\n", test_case, minSize);

	}

	return 0;	// �������� �� �ݵ�� 0�� �����ؾ� �մϴ�.
}
