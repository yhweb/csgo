#include <iostream>
#include <Windows.h>
using namespace std;



//void test() {
//	//1. ͨ�������� ��ȡ���ھ��
//	//2. ͨ�����ھ����ȡ����id
//	//3. ͨ������id��ȡ���̾��
//	//4. ͨ�����̾�� ����̶�ȡ����
//
//
//	//����Ŀ ����Ϊ������Ŀ
//	//��������
//	//���ھ��
//	//�ַ�������
//	//����
//	//����
//	//MessageBox(0, (LPCWSTR)"13213132313", (LPCWSTR)"����", 1);
//
//	//���ھ��
//	//���ھ������HWND
//	//FindWindowA
//	//SetWindowTextA
//	//GetWindows
//	HWND ���ھ�� = FindWindowA("Valve001", NULL);
//	printf("%p\r\n", ���ھ��);
//	LPSTR name = { 0 };
//	GetWindowTextA(���ھ��, name, sizeof(name));
//	printf("%s\r\n", name);
//	//SetWindowTextA(jubing, (LPCSTR)"bbbb");
//
//	//��ȡ�߳�tip �ͽ���pid
//	DWORD pid, tid;
//	tid = GetWindowThreadProcessId(���ھ��, &pid);
//	printf("��ַpid: %X\r\n", pid);
//	printf("pid: %d\r\n", pid);
//	printf("��ַtid: %X\r\n", tid);
//	printf("tid: %d\r\n", tid);
//
//	//��ȡ���̾���ĺ���
//	//Ȩ��
//	//�Ƿ񼯳ɾ��
//	//����pid
//	HANDLE ���̾�� = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
//	printf("���̾��=%p \r\n", ���̾��);
//	float call_back_value = 0;
//	//����
//	//Ҫ��ȡ�ĵ�ַ
//	//������ݵ�λ��
//	//���ݳ���
//	//0
//	ReadProcessMemory(���̾��, (LPCVOID)0x5ED4235C, &call_back_value, sizeof(call_back_value), 0);
//	printf("����ֵ=%X  ����ֵ=%f ����ֵ=%u\r\n", call_back_value, call_back_value, call_back_value);// GetLastError();
//	getchar();
//	//lpcvoid ��Ϸ���ݵ�ַ
//	//lpvoid ���ڴ�����ݵĵ�ַ
//}
//int R4(UINT_PTR �ڴ��ַ) {
//	printf("�ڴ��ַ:%X\r\n", �ڴ��ַ);
//	HWND w_jb = FindWindowA("Valve001", NULL);
//	DWORD tid = 0, pid = 0;
//	tid = GetWindowThreadProcessId(w_jb, &pid);
//	HANDLE jincheng_jb = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
//	unsigned int call_back_value = 0;
//	ReadProcessMemory(jincheng_jb, (LPCVOID)�ڴ��ַ, &call_back_value, 4, 0);
//	printf("����ֵ=%X  ����ֵ=%d ����ֵ=%u\r\n", call_back_value, call_back_value, call_back_value);// GetLastError();
//	//cout << GetLastError() << endl;
//	CloseHandle(jincheng_jb);
//	return call_back_value;
//}

#include <windows.h>
#include <stdio.h>
HWND getGameWJb() {
	//return FindWindowA("Valve001", NULL);
	return FindWindowA("CabinetWClass", NULL);
}

DWORD r4(UINT_PTR addr) {
	HWND w_jb = getGameWJb();
	DWORD tid = 0, pid = 0;
	tid = GetWindowThreadProcessId(w_jb, &pid);
	HANDLE jincheng_jb = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	unsigned int call_back_value = 0;
	ReadProcessMemory(jincheng_jb, (LPCVOID)addr, &call_back_value, 4, 0);
	//printf("����ֵ=%X  ����ֵ=%d ����ֵ=%u\r\n", call_back_value, call_back_value, call_back_value);// GetLastError();
	CloseHandle(jincheng_jb);
	return call_back_value;
}
int w4(UINT_PTR addr, DWORD date) {
	HWND w_jb = getGameWJb();
	DWORD tid = 0, pid = 0;
	tid = GetWindowThreadProcessId(w_jb, &pid);
	HANDLE jincheng_jb = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	unsigned int call_back_value = WriteProcessMemory(jincheng_jb, (LPVOID)addr, &date, 4, 0);
	CloseHandle(jincheng_jb);
	return call_back_value;
}
void testRw() {
	//2c600000
	//[[0F0C5D08]+939d34]+21c
	int hp = r4(r4(r4(0x0F0C5D08) + 0x939D34) + 0x21c);
	printf("%d\r\n", hp, __LINE__);// __FILE__ ��ʾ����Դ�ļ�

	int addr = r4(r4(0x0F0C5D08) + 0x939D34) + 0x21c;
	printf("%X\r\n", addr);
	DWORD date = 99;
	w4(addr, date);
	printf("char��ռ�ռ�=%d \r\n", sizeof(char));
	printf("short��ռ�ռ�=%d \r\n", sizeof(short));
	printf("int��ռ�ռ�=%d \r\n", sizeof(int));
	printf("long��ռ�ռ�=%d \r\n", sizeof(long));

	printf("UINT_PTR��ռ�ռ�=%d \r\n", sizeof(UINT_PTR));
	printf("LPVOID��ռ�ռ�=%d \r\n", sizeof(LPVOID));

	printf("DWORD��ռ�ռ�=%d \r\n", sizeof(DWORD));


	getchar();
}
void createRT() {
	HWND w_jb = getGameWJb();
	DWORD tid = 0, pid = 0;
	tid = GetWindowThreadProcessId(w_jb, &pid);
	char name[100];
	int c = GetWindowText(w_jb, (LPWSTR)name, 100);
	printf("���ָ��� %d\r\n", c);
	cout << strlen(name) << endl;
	cout << "��������: " << name << endl;
	HANDLE jincheng_jb = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	//�ؼ����� ���̾�� call��ַ call����
	//CreateRemoteThread(
	//	jincheng_jb,//���̾��
	//	0,
	//	0,//��ջ��С
	//	(LPTHREAD_START_ROUTINE)0x411370,//call�ĵ�ַ
	//	(LPVOID)123,//call�Ĳ���
	//	0,
	//	0);
	CloseHandle(jincheng_jb);
}


//32��ʹ��
//extern "C" UINT32 __stdcall  mycall();//��������
//extern "C" UINT32 __stdcall myadd();

//x64��ʹ��
extern "C" UINT64 mycall();//��������
extern "C" UINT64 myadd();

int main() {
	//64λ 10���� �з��� lld
	//64λ 10���� �޷��� llu
	//64λ 16���� llu
	//printf("mycall����ֵ = %llX\r\n", mycall());
	//printf("myadd����ֵ = %llX\r\n", myadd());

	createRT();

	getchar();

	return 0;
}


