#include <iostream>
#include <Windows.h>
using namespace std;



//void test() {
//	//1. 通过窗口类 获取窗口句柄
//	//2. 通过窗口句柄获取进行id
//	//3. 通过进程id获取进程句柄
//	//4. 通过进程句柄 跨进程读取数据
//
//
//	//点项目 设置为启动项目
//	//弹出窗口
//	//窗口句柄
//	//字符串描述
//	//标题
//	//类型
//	//MessageBox(0, (LPCWSTR)"13213132313", (LPCWSTR)"标题", 1);
//
//	//窗口句柄
//	//窗口句柄类型HWND
//	//FindWindowA
//	//SetWindowTextA
//	//GetWindows
//	HWND 窗口句柄 = FindWindowA("Valve001", NULL);
//	printf("%p\r\n", 窗口句柄);
//	LPSTR name = { 0 };
//	GetWindowTextA(窗口句柄, name, sizeof(name));
//	printf("%s\r\n", name);
//	//SetWindowTextA(jubing, (LPCSTR)"bbbb");
//
//	//读取线程tip 和进程pid
//	DWORD pid, tid;
//	tid = GetWindowThreadProcessId(窗口句柄, &pid);
//	printf("地址pid: %X\r\n", pid);
//	printf("pid: %d\r\n", pid);
//	printf("地址tid: %X\r\n", tid);
//	printf("tid: %d\r\n", tid);
//
//	//获取进程句柄的函数
//	//权限
//	//是否集成句柄
//	//进程pid
//	HANDLE 进程句柄 = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
//	printf("进程句柄=%p \r\n", 进程句柄);
//	float call_back_value = 0;
//	//进程
//	//要读取的地址
//	//存放数据的位置
//	//数据长度
//	//0
//	ReadProcessMemory(进程句柄, (LPCVOID)0x5ED4235C, &call_back_value, sizeof(call_back_value), 0);
//	printf("返回值=%X  返回值=%f 返回值=%u\r\n", call_back_value, call_back_value, call_back_value);// GetLastError();
//	getchar();
//	//lpcvoid 游戏数据地址
//	//lpvoid 用于存放数据的地址
//}
//int R4(UINT_PTR 内存地址) {
//	printf("内存地址:%X\r\n", 内存地址);
//	HWND w_jb = FindWindowA("Valve001", NULL);
//	DWORD tid = 0, pid = 0;
//	tid = GetWindowThreadProcessId(w_jb, &pid);
//	HANDLE jincheng_jb = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
//	unsigned int call_back_value = 0;
//	ReadProcessMemory(jincheng_jb, (LPCVOID)内存地址, &call_back_value, 4, 0);
//	printf("返回值=%X  返回值=%d 返回值=%u\r\n", call_back_value, call_back_value, call_back_value);// GetLastError();
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
	//printf("返回值=%X  返回值=%d 返回值=%u\r\n", call_back_value, call_back_value, call_back_value);// GetLastError();
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
	printf("%d\r\n", hp, __LINE__);// __FILE__ 表示所有源文件

	int addr = r4(r4(0x0F0C5D08) + 0x939D34) + 0x21c;
	printf("%X\r\n", addr);
	DWORD date = 99;
	w4(addr, date);
	printf("char所占空间=%d \r\n", sizeof(char));
	printf("short所占空间=%d \r\n", sizeof(short));
	printf("int所占空间=%d \r\n", sizeof(int));
	printf("long所占空间=%d \r\n", sizeof(long));

	printf("UINT_PTR所占空间=%d \r\n", sizeof(UINT_PTR));
	printf("LPVOID所占空间=%d \r\n", sizeof(LPVOID));

	printf("DWORD所占空间=%d \r\n", sizeof(DWORD));


	getchar();
}
void createRT() {
	HWND w_jb = getGameWJb();
	DWORD tid = 0, pid = 0;
	tid = GetWindowThreadProcessId(w_jb, &pid);
	char name[100];
	int c = GetWindowText(w_jb, (LPWSTR)name, 100);
	printf("名字个数 %d\r\n", c);
	cout << strlen(name) << endl;
	cout << "窗口名字: " << name << endl;
	HANDLE jincheng_jb = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	//关键参数 进程句柄 call地址 call参数
	//CreateRemoteThread(
	//	jincheng_jb,//进程句柄
	//	0,
	//	0,//堆栈大小
	//	(LPTHREAD_START_ROUTINE)0x411370,//call的地址
	//	(LPVOID)123,//call的参数
	//	0,
	//	0);
	CloseHandle(jincheng_jb);
}


//32下使用
//extern "C" UINT32 __stdcall  mycall();//函数声明
//extern "C" UINT32 __stdcall myadd();

//x64下使用
extern "C" UINT64 mycall();//函数声明
extern "C" UINT64 myadd();

int main() {
	//64位 10进制 有符号 lld
	//64位 10进制 无符号 llu
	//64位 16进制 llu
	//printf("mycall返回值 = %llX\r\n", mycall());
	//printf("myadd返回值 = %llX\r\n", myadd());

	createRT();

	getchar();

	return 0;
}


