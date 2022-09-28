#include <stdio.h>
#include <setjmp.h>

static jmp_buf set, set2;

void f1(), f2(), f3(), f4(), f5(), f6(), f7(), f8();

int main()
{
	if (setjmp(set2) == 0)	
	{
		printf("main start:\n");
		f1();
	}
	else
	{
		printf("main from jump\n");
		f8();
	}
	return (0);
}

void f1()
{
	printf("f1()\n");
	if (setjmp(set) == 0)
		f2();
	else
		f5();
}

void f2()
{
	printf("f2()\n");
	f3();
}

void f3()
{
	printf("f3()\n");
	f4();
}

void f4()
{
	printf("f4()\n");
	longjmp(set, 1);
}

void f5()
{
	printf("f5()\n");
	f6();
}

void f6()
{
	printf("f6()\n");
	f7();
}

void f7()
{
	printf("f7()\n");
	longjmp(set2, 1);
}

void f8()
{
	printf("f8()\n");
}
