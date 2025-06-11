#include<string>
#include<graphics.h>
#include<vector>
#include"player.h"


int idx_current_anime = 0;

const int PLAYER_ANIME_NUM = 6;
const int PLAYER_SPEED = 5;

IMAGE  img_player_left[PLAYER_ANIME_NUM];
IMAGE  img_player_right[PLAYER_ANIME_NUM];
IMAGE  img_background;
POINT  player_position = { 600,300 };




//�޸�putimage����ʹ֮ʵ�ֶ��黯�����Ĵ���
#pragma comment(lib,"MSIMG32.LIB")
inline void putimage_alpha(int x, int y, IMAGE* img) 
{
	int w = img->getwidth();
	int h = img->getwidth();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}


void load_animation()
{
	for (SIZE_T i = 0; i < PLAYER_ANIME_NUM; i++) {
		//�ֱ����ƺ����ƶ���װ������
		std::wstring path = L"img/player_left_" + std::to_wstring(i) + L".png";
		loadimage(&img_player_left[i], path.c_str());
		path = L"img/player_right_" + std::to_wstring(i) + L".png";
		loadimage(&img_player_right[i], path.c_str());
	}
}


int main() {

	Player player1; //�������1����
	load_animation();  //�������ﶯ��
	loadimage(&img_background, _T("img/background.png")); //���ر���ͼ
	initgraph(1280, 720); //��ʼ������

	bool running = true;

	ExMessage msg;

	BeginBatchDraw();

	while (running) {

		DWORD start_time = GetTickCount();

		player1.move(&msg); //����ƶ�

		static int counter = 0;
		//ÿ���ѭ�� ��������һ֡
		if (++counter % 5 == 0) {
			idx_current_anime++;
		}

		idx_current_anime %= PLAYER_ANIME_NUM; //���ﶯ�����һ֡ʱ����

		cleardevice();
		putimage(0, 0, &img_background); //���Ʊ���ͼ

		player_position = player1.get_position();

		putimage_alpha(player_position.x, player_position.y, &img_player_left[idx_current_anime]); //�����������ƶ���
		FlushBatchDraw();


		DWORD end_time = GetTickCount();
		DWORD delta_time = start_time - end_time;
		if (delta_time < 1000 / 144)
		{
			Sleep(1000 / 144 - delta_time);
		}
		

	}
	EndBatchDraw();

	return 0;
}