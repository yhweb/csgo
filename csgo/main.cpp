//Titans assualt cube example ESP


#include <Windows.h>
#include <iostream>

DWORD entityListStart = 0x0050F4F4;
DWORD viewMatrix = 0x501AE8;//矩阵基地址
DWORD healthOffset = 0xF8;//血量偏移?
HWND hwndAC_Client;
HBRUSH Brush;
HDC hdcAC_client;
HFONT Font;
float Matrix[16];//定义矩阵
COLORREF TextCOLOR;//文本颜色
COLORREF TextCOLORRED;//文本红色

//defining our vectors
//定义向量
struct Vec3
{
	float x, y, z;
};

struct Vec4
{
	float x, y, z, w;
};

struct Vec2
{
	float x, y;
};

//These two function are from a old fleep post, i was able to use them to create the box style however this was just to save time :) Thx Fleep
//这两个功能来自旧的 Fleep 帖子，我可以使用它们来创建盒子样式，但这只是为了节省时间 :) Thx Fleep
void DrawFilledRect(int x, int y, int w, int h)
{
	RECT rect = { x, y, x + w, y + h };
	FillRect(hdcAC_client, &rect, Brush);
}


void DrawBorderBox(int x, int y, int w, int h, int thickness)
{

	DrawFilledRect(x, y, w, thickness);

	DrawFilledRect(x, y, thickness, h);

	DrawFilledRect((x + w), y, thickness, h);

	DrawFilledRect(x, y + h, w + thickness, thickness);
}


void DrawLine(int targetX, int targetY)
{
	MoveToEx(hdcAC_client, 1920, 1080, NULL);
	LineTo(hdcAC_client, targetX, targetY);

}


void DrawString(int x, int y, COLORREF color, const char* text)
{
	SetTextAlign(hdcAC_client, TA_CENTER | TA_NOUPDATECP);

	SetBkColor(hdcAC_client, RGB(0, 0, 0));
	SetBkMode(hdcAC_client, TRANSPARENT);

	SetTextColor(hdcAC_client, color);

	SelectObject(hdcAC_client, Font);

	TextOutA(hdcAC_client, x, y, text, strlen(text));

	DeleteObject(Font);
}
//this is the world to screen function for openGL
bool WorldToScreen(Vec3 pos, Vec2& screen, float matrix[16], int windowWidth, int windowHeight) // 3D to 2D
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	Vec4 clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	//4x4横矩阵
	//0  1  2  3
	//4  5  6  7
	//8  9  10 11
	//12 13 14 15

	//4x4竖矩阵
	//0 4 8  12
	//1 5 9  13
	//2 6 10 14
	//3 7 11 15

	//裁剪坐标 -> ndc坐标 -> 屏幕坐标

	//根据w判断是否进行剔除 不进行画线操作
	if (clipCoords.w < 0.1f)
		return false;

	//perspective division, dividing by clip.W = Normalized Device Coordinates
	//透视除法，除以剪辑。W = 标准化设备坐标
	//除以w得到ndc坐标
	Vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	//Transform to window coordinates
	//转换windows坐标
	//screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	//screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	screen.x = (windowWidth / 2 * NDC.x) + (windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (windowHeight / 2);
	return true;
}


int mainThread()
{
	TextCOLOR = RGB(255, 255, 255);
	hwndAC_Client = FindWindow(0, TEXT("Counter-Strike: Global Offensive"));//Gets Window

	if (hwndAC_Client == NULL)
	{
		exit(0);
	}

	DWORD entityList = *(DWORD*)(entityListStart + 0x4);

	while (true)
	{
		//拷贝矩阵
		memcpy(&Matrix, (PBYTE*)(viewMatrix), sizeof(Matrix));
		hdcAC_client = GetDC(hwndAC_Client);
		//Base of player
		Vec2 vScreen;
		//Head of player
		Vec2 vHead;

		//Sets the ammount of Players
		//读取并设置玩家数量
		DWORD amountOfPlayers = *(DWORD*)(0x50F500);


		//our entity list loop
		//遍历玩家
		for (short int i = 0; i < amountOfPlayers; i++)
		{


			//Create the entity
			//创建方框
			DWORD entity = *(DWORD*)(entityList + 0x4 * i);

			if (entity != NULL)
			{

				//The entitys Pos
				//玩家坐标
				float enemyX = *(float*)(entity + 0x34);
				float enemyY = *(float*)(entity + 0x38);
				float enemyZ = *(float*)(entity + 0x3C);

				Vec3 enemyPos = { enemyX, enemyY, enemyZ };

				//Enemys Head Pos
				//敌人头部位置
				float enemyXHead = *(float*)(entity + 0x4);
				float enemyYHead = *(float*)(entity + 0x8);
				float enemyZHead = *(float*)(entity + 0xC);

				Vec3 enemyHeadPos = { enemyXHead, enemyYHead, enemyZHead };


				//Sets each entitys health
				//敌人的血量
				DWORD health = *(DWORD*)(entity + healthOffset);

				//converts 3d to 2d
				//将 3d 转换为 2d 画出方框
				//获取敌人2d的xy坐标  敌人坐标  相对于屏幕的位置  矩阵    窗口大小
				if (WorldToScreen(enemyPos, vScreen, Matrix, 1920, 1080))
				{

					//获取敌人2d的xy坐标  敌人头部坐标  相对于屏幕的位置  矩阵    窗口大小
					if (WorldToScreen(enemyHeadPos, vHead, Matrix, 1920, 1080))
					{


						//Creates the head height
						//创建头部高度
						float head = vHead.y - vScreen.y;
						//Creates Width
						//创建宽度
						float width = head / 2;
						//Creates Center
						//创建中心
						float center = width / -2;
						//Creates Extra area above head
						//在头部上方创建额外区域
						float extra = head / -6;

						//Sets the Brush Color
						//设置画笔颜色
						Brush = CreateSolidBrush(RGB(158, 66, 244));
						//Draws the box
						//绘制盒子
						DrawBorderBox(vScreen.x + center, vScreen.y, width, head - extra, 1);
						DeleteObject(Brush);


						//Draw our heath by converting a int to a char
						//通过将 int 转换为 char 来显示血量
						char healthChar[255];
						sprintf_s(healthChar, sizeof(healthChar), " %i", (int)(health));
						DrawString(vScreen.x, vScreen.y, TextCOLOR, healthChar);


						//Turns on snaplines
						if (GetKeyState(VK_F2) & 1)
						{
							DrawLine(vScreen.x, vScreen.y);
						}
					}
				}
			}
		}
		//This prevents a fat memory leak
		Sleep(1);
		DeleteObject(hdcAC_client);



	}
}

//creates our thread
//创建线程
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)mainThread, NULL, NULL, NULL);

	}

	return TRUE;
}