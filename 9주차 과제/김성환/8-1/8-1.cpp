#define _CRT_SECURE_NO_WARNINGS
#include "stack8_1.h"
#include <time.h>

int main()
{
	time_t start, end;
	start = clock();

	FILE* fp = fopen("input08_01.txt", "r"); // 입력 데이터 파일
	int T, n; // T : 테스트 케이스, n : 입력 개수
	int mv; // 입력값 임시저장 변수, 최대값;
	Stack s = create(); // Stack size 100
	contents tmp = { 0, 0 };


	long long sum = 0;

	fscanf(fp, "%d", &T); // T load
	while (T--) // T회 실행
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

			if (tmp.num > mv) // 읽은값이 지금까지 가장 큰 수라면, 지금까지 나온 수만큼 sum에 +, 스택 초기화
			{
				sum += i;
				s->top = -1;
				push(s, tmp.num);
				s->contents[s->top].data = i;
				mv = tmp.num;
			}
			else // tmp <= mv
			{
				if (tmp.num < s->contents[s->top].num) // 이전값보다 작은 값이면 push
				{
					push(s, tmp.num);
				}
				else
				{
					while (s->top > -1 && tmp.num >= s->contents[s->top].num) // 더 큰 수가 나올때까지 pop
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