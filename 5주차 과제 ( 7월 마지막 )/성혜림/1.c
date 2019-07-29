#pragma warning (disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 4
int yes_or_no(char buf[]); 
int main(void) {

	char *str[SIZE];
	printf("Enter IP address : \n");

	int count = 0;
	for (int i = 0; i < SIZE; i++) {
		if (yes_or_no(str) == 1)
			count++;
	}
	if (count == SIZE)
		printf("Yes\n");
	else
		printf("No\n");

	getchar(); getchar();
	return 0;
}
int yes_or_no(char buf[]) {

	srand((unsigned int)time(NULL));
	
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		buf[i] = rand() % 10;
		sum = sum * 10 + (buf[i] - '0');
		if (sum > 0 && sum < 255)
			return 1;
		return 0;
	}
}