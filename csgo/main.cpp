//Titans assualt cube example ESP


#include <Windows.h>
#include <iostream>

DWORD entityListStart = 0x0050F4F4;
DWORD viewMatrix = 0x501AE8;//�������ַ
DWORD healthOffset = 0xF8;//Ѫ��ƫ��?
HWND hwndAC_Client;
HBRUSH Brush;
HDC hdcAC_client;
HFONT Font;
float Matrix[16];//�������
COLORREF TextCOLOR;//�ı���ɫ
COLORREF TextCOLORRED;//�ı���ɫ

//defining our vectors
//��������
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
//�������������Ծɵ� Fleep ���ӣ��ҿ���ʹ������������������ʽ������ֻ��Ϊ�˽�ʡʱ�� :) Thx Fleep
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

	//4x4�����
	//0  1  2  3
	//4  5  6  7
	//8  9  10 11
	//12 13 14 15

	//4x4������
	//0 4 8  12
	//1 5 9  13
	//2 6 10 14
	//3 7 11 15

	//�ü����� -> ndc���� -> ��Ļ����

	//����w�ж��Ƿ�����޳� �����л��߲���
	if (clipCoords.w < 0.1f)
		return false;

	//perspective division, dividing by clip.W = Normalized Device Coordinates
	//͸�ӳ��������Լ�����W = ��׼���豸����
	//����w�õ�ndc����
	Vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	//Transform to window coordinates
	//ת��windows����
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
		//��������
		memcpy(&Matrix, (PBYTE*)(viewMatrix), sizeof(Matrix));
		hdcAC_client = GetDC(hwndAC_Client);
		//Base of player
		Vec2 vScreen;
		//Head of player
		Vec2 vHead;

		//Sets the ammount of Players
		//��ȡ�������������
		DWORD amountOfPlayers = *(DWORD*)(0x50F500);


		//our entity list loop
		//�������
		for (short int i = 0; i < amountOfPlayers; i++)
		{


			//Create the entity
			//��������
			DWORD entity = *(DWORD*)(entityList + 0x4 * i);

			if (entity != NULL)
			{

				//The entitys Pos
				//�������
				float enemyX = *(float*)(entity + 0x34);
				float enemyY = *(float*)(entity + 0x38);
				float enemyZ = *(float*)(entity + 0x3C);

				Vec3 enemyPos = { enemyX, enemyY, enemyZ };

				//Enemys Head Pos
				//����ͷ��λ��
				float enemyXHead = *(float*)(entity + 0x4);
				float enemyYHead = *(float*)(entity + 0x8);
				float enemyZHead = *(float*)(entity + 0xC);

				Vec3 enemyHeadPos = { enemyXHead, enemyYHead, enemyZHead };


				//Sets each entitys health
				//���˵�Ѫ��
				DWORD health = *(DWORD*)(entity + healthOffset);

				//converts 3d to 2d
				//�� 3d ת��Ϊ 2d ��������
				//��ȡ����2d��xy����  ��������  �������Ļ��λ��  ����    ���ڴ�С
				if (WorldToScreen(enemyPos, vScreen, Matrix, 1920, 1080))
				{

					//��ȡ����2d��xy����  ����ͷ������  �������Ļ��λ��  ����    ���ڴ�С
					if (WorldToScreen(enemyHeadPos, vHead, Matrix, 1920, 1080))
					{


						//Creates the head height
						//����ͷ���߶�
						float head = vHead.y - vScreen.y;
						//Creates Width
						//�������
						float width = head / 2;
						//Creates Center
						//��������
						float center = width / -2;
						//Creates Extra area above head
						//��ͷ���Ϸ�������������
						float extra = head / -6;

						//Sets the Brush Color
						//���û�����ɫ
						Brush = CreateSolidBrush(RGB(158, 66, 244));
						//Draws the box
						//���ƺ���
						DrawBorderBox(vScreen.x + center, vScreen.y, width, head - extra, 1);
						DeleteObject(Brush);


						//Draw our heath by converting a int to a char
						//ͨ���� int ת��Ϊ char ����ʾѪ��
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
//�����߳�
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)mainThread, NULL, NULL, NULL);

	}

	return TRUE;
}