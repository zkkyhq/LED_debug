#include <stdio.h>

int main(void)
{
	//char a[] = "谢谢合作";
	//printf("%d\n", strlen(a)); //12
	//printf("%d\n", sizeof(a)); //13

	/*unsigned char a = 129;
	char b = 129; //-127
	printf("%d\n", a);
	printf("%d\n", b);
	printf("%x\n", a);
	printf("%x\n", b);
	printf("%u\n", a);
	printf("%u\n", b);*/

	char c = 129;
	int d = 1;
	d += c;
	printf("%d\n", d);

	return 0;
}
