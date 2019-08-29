#define _CRT_SECURE_NO_WARNINGS
#include "stack8_1.h"
#include <time.h>

int main()
{
	time_t start, end;
	start = clock();

	FILE* fp = fopen("input08_01.txt", "r"); // �Է� ������ ����
	int T, n; // T : �׽�Ʈ ���̽�, n : �Է� ����
	int mv; // �Է°� �ӽ����� ����, �ִ밪;
	Stack s = create(); // Stack size 100
	contents tmp = { 0, 0 };


	long long sum = 0;

	fscanf(fp, "%d", &T); // T load
	while (T--) // Tȸ ����
	{
		sum = 0;
		fscanf(fp, "%d", &n); // n load
		s->top = -1;
		fscanf(fp, "%d", &tmp.num);
		push(s, tmp.num);
		mv = tmp.num;
		for (int i = 1; i < n; i++)
		{
			fscanf(fp, "%d", &tmp.num);
			tmp.data = 0;

			if (tmp.num > mv) // �������� ���ݱ��� ���� ū �����, ���ݱ��� ���� ����ŭ sum�� +, ���� �ʱ�ȭ
			{
				sum += i;
				s->top = -1;
				push(s, tmp.num);
				s->contents[s->top].data = i;
				mv = tmp.num;
			}
			else // tmp <= mv
			{
				if (tmp.num < s->contents[s->top].num) // ���������� ���� ���̸� push
				{
					push(s, tmp.num);
				}
				else
				{
					while (s->top > -1 && tmp.num >= s->contents[s->top].num) // �� ū ���� ���ö����� pop
					{
						tmp.data += (s->contents[s->top].data + 1);
						pop(s);
					}
					push(s, tmp.num);
					s->contents[s->top].data = tmp.data;
					sum += s->contents[s->top].data;
				}
			}
			sum %= 1000000;
		}
		printf("%lld\n", (sum));
	}
	fclose(fp);
	end = clock();

	printf("Time : %f\n", ((end - start) / (float)CLOCKS_PER_SEC));

	return 0;
}