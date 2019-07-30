#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

	char input[500] = { NULL, };
	int leng, sum_array[100], count = 0, sum = 0, answer;

	gets(input);
	leng = strlen(input);
	for (int i = 0; i < leng; i++)
	{
		if (48 <= input[i] && input[i] <= 57)
		{
			answer = input[i] - 48;
			while (48<=input[i+1]&&input[i+1]<=57) {
				answer *= 10;
				answer += (input[i + 1] - 48);
				i++;
			}
			sum_array[count] = answer;
			count++;
		}
	}
	for (int i = 0; i < count-1; i++)
		printf("%d+", sum_array[i]);
	for (int i = 0; i < count; i++)
		sum += sum_array[i];
	printf("%d=%d", sum_array[count - 1], sum);

	return 0;
}