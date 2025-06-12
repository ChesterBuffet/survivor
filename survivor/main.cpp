#include"main.h"

int idx_current_anime = 0;
const int PLAYER_ANIME_NUM = 6;
const int PLAYER_SPEED = 5;


IMAGE  img_background;
IMAGE  img_shadow;
POINT  player_position = { 600,300 };
Animation  anime_left_player(_T("img/player_left_%d.png"), 6, 45);
Animation  anime_right_player(_T("img/player_right_%d.png"), 6, 45);
const int PLAYER_WIDTH = 80;  //玩家高度
const int PLAYER_HEIGHT = 80; //玩家宽度
const int SHADOW_WIDTH = 32; //阴影宽度
const int WINDOWS_WIDTH = 1280; //窗口尺寸-宽度
const int WINDOWS_HEIGHT = 720; //窗口尺寸-高度


void DrawPlayer(int delta, Player *player,IMAGE *img_shadow)
{

		POINT  player_position = player->get_position();
	int pos_shadow_x = player_position.x + (PLAYER_WIDTH / 2 - SHADOW_WIDTH / 2);
	int pos_shadow_y = player_position.y + PLAYER_HEIGHT - 8;
		putimage_alpha(pos_shadow_x, pos_shadow_y, img_shadow); //绘制角色阴影
		putimage(pos_shadow_x, pos_shadow_y, img_shadow); //绘制角色阴影
	

	static bool facing_left = true; //使用静态变量继承角色方向
	if (player->left_right()>0) {
		facing_left = true;
	}
	else if (player->left_right() < 0) {
		facing_left = false;
	}

	if (facing_left)
		anime_left_player.play(player_position.x,player_position.y,delta);  //绘制左移动画
	else
		anime_right_player.play(player_position.x, player_position.y, delta); //绘制右移动画
}


int main() {

	Player player1; //创建玩家1对象
	//load_animation();  //加载人物动画
	loadimage(&img_background, _T("img/background.png")); //加载背景图
	initgraph(WINDOWS_WIDTH, WINDOWS_HEIGHT); //初始化界面
	loadimage(&img_shadow, _T("img/shadow_player(1).png")); //加载角色阴影
	bool running = true;

	ExMessage msg;

	BeginBatchDraw();

	while (running) {

		DWORD start_time = GetTickCount();

		player1.move(&msg); //玩家移动

		static int counter = 0;
		//每五次循环 动画播放一帧
		if (++counter % 5 == 0) {
			idx_current_anime++;
		}

		idx_current_anime %= PLAYER_ANIME_NUM; //到达动画最后一帧时归零

		cleardevice();
		putimage(0, 0, &img_background); //绘制背景图




		//POINT  player_position = player1.get_position();
		//int pos_shadow_x = player_position.x + (PLAYER_WIDTH / 2 - SHADOW_WIDTH / 2);
		//int pos_shadow_y = player_position.y + PLAYER_HEIGHT - 8;
		//putimage_alpha(0, 0, &img_shadow); //绘制角色阴影



		DrawPlayer(1000/144,&player1, &img_shadow);  //绘制角色移动动作和阴影
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