#include"main.h"

int idx_current_anime = 0;
const int PLAYER_ANIME_NUM = 6;
const int PLAYER_SPEED = 5;


IMAGE  img_background;
IMAGE  img_shadow;
POINT  player_position = { 600,300 };
Animation  anime_left_player(_T("img/player_left_%d.png"), 6, 45);
Animation  anime_right_player(_T("img/player_right_%d.png"), 6, 45);
const int PLAYER_WIDTH = 80;  //��Ҹ߶�
const int PLAYER_HEIGHT = 80; //��ҿ��
const int SHADOW_WIDTH = 32; //��Ӱ���
const int WINDOWS_WIDTH = 1280; //���ڳߴ�-���
const int WINDOWS_HEIGHT = 720; //���ڳߴ�-�߶�


void DrawPlayer(int delta, Player *player,IMAGE *img_shadow)
{

		POINT  player_position = player->get_position();
	int pos_shadow_x = player_position.x + (PLAYER_WIDTH / 2 - SHADOW_WIDTH / 2);
	int pos_shadow_y = player_position.y + PLAYER_HEIGHT - 8;
		putimage_alpha(pos_shadow_x, pos_shadow_y, img_shadow); //���ƽ�ɫ��Ӱ
		putimage(pos_shadow_x, pos_shadow_y, img_shadow); //���ƽ�ɫ��Ӱ
	

	static bool facing_left = true; //ʹ�þ�̬�����̳н�ɫ����
	if (player->left_right()>0) {
		facing_left = true;
	}
	else if (player->left_right() < 0) {
		facing_left = false;
	}

	if (facing_left)
		anime_left_player.play(player_position.x,player_position.y,delta);  //�������ƶ���
	else
		anime_right_player.play(player_position.x, player_position.y, delta); //�������ƶ���
}


int main() {

	Player player1; //�������1����
	//load_animation();  //�������ﶯ��
	loadimage(&img_background, _T("img/background.png")); //���ر���ͼ
	initgraph(WINDOWS_WIDTH, WINDOWS_HEIGHT); //��ʼ������
	loadimage(&img_shadow, _T("img/shadow_player(1).png")); //���ؽ�ɫ��Ӱ
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




		//POINT  player_position = player1.get_position();
		//int pos_shadow_x = player_position.x + (PLAYER_WIDTH / 2 - SHADOW_WIDTH / 2);
		//int pos_shadow_y = player_position.y + PLAYER_HEIGHT - 8;
		//putimage_alpha(0, 0, &img_shadow); //���ƽ�ɫ��Ӱ



		DrawPlayer(1000/144,&player1, &img_shadow);  //���ƽ�ɫ�ƶ���������Ӱ
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