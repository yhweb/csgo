// A023_����CALL.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <Windows.h>
int call00()
{
	printf("call00 �޲��� call0_test  �к�=%d\r\n", __LINE__);
	return 0x123;
}


int call01(int a)
{
	printf("call01 ����1=%d   �к�=%d\r\n", a, __LINE__);
	return a + 2;
}
int call02(int a, int b)
{
	printf("call02 ����1=%d ����2=%d �к�=%d\r\n", a, b, __LINE__);
	return a + b + 3;
}

int main()
{
	//	MessageBoxA(0, 0, 0, 0);//ctrl+G ת�� MessageBoxA �¶�
	printf("MessageBoxA=%p �к�=%d \r\n", MessageBoxA, __LINE__);
	int ���� = 1;
	while (1)
	{
		printf("call00=%p call01=%p,call02=%p \n", call00, call01, call02);
		getchar();
		printf("����=%d,�к�=%d \r\n", ����++, __LINE__);
	}
	return 1;
}
