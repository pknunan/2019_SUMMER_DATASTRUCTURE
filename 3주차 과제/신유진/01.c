#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100
int main() {
	char str[MAX];
	int index;		
	int tmp,tmp_sum=0, count = 0, sum = 0, m = 0;
	gets(str);
	int length = strlen(str);
	for (int i = 0; i < length; i++) {
		count = 0;
		if (isdigit(str[i]) != 0){ 							//0이 아니면 str[i]는 숫자
			count++;
			for (int j = i + 1; j < length; j++) {
				if (isdigit(str[j]) != 0) {
					count++;
				}
				else{
					index = i;
					break;
				}
			}
			if (count < 2) {
				tmp = str[i] - 48;
				sum += tmp;
			}
			else {
				for (int k = i; k < i + count; k++) {
					tmp = str[k] - 48;
					for (int p = count - 2; p >= 0; p--) {
						tmp *= 10;
						count--;
					}
				}sum += tmp;
			}
		}
	}
	printf("%d", sum);
	return 0;
}