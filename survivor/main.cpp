#include<string>
#include<graphics.h>


int idx_current_anime = 0;

const int PLAYER_ANIME_NUM = 6;
const int PLAYER_SPEED = 5;

IMAGE  img_player_left[PLAYER_ANIME_NUM];
IMAGE  img_player_right[PLAYER_ANIME_NUM];
IMAGE  img_background;
POINT  player_position = { 600,300 };




//修改putimage函数使之实现对虚化背景的处理
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
		//分别将左移和右移动画装入数组
		std::wstring path = L"img/player_left_" + std::to_wstring(i) + L".png";
		loadimage(&img_player_left[i], path.c_str());
		path = L"img/player_right_" + std::to_wstring(i) + L".png";
		loadimage(&img_player_right[i], path.c_str());
	}
}


int main() {

	load_animation();  //加载人物动画
	loadimage(&img_background, _T("img/background.png")); //加载背景图
	initgraph(1280, 720); //初始化界面

	bool running = true;

	ExMessage msg;
	
	


	BeginBatchDraw();

	while (running) {

		DWORD start_time = GetTickCount();

		while (peekmessage(&msg)) {

			if (msg.message == WM_KEYDOWN) {
				switch (msg.vkcode) {
				case VK_UP:
					is_move_up =true;
					break;
				case VK_DOWN:
					is_move_down = true;
					break;
				case VK_LEFT:
					is_move_left = true;
					break;
				case VK_RIGHT:
					is_move_right = true;
					break;
				default:
					break;
				}
			}
			else if(msg.message == WM_KEYUP)
			{
				switch (msg.vkcode) {
				case VK_UP:
					is_move_up = false;
					break;
				case VK_DOWN:
					is_move_down = false;
					break;
				case VK_LEFT:
					is_move_left = false;
					break;
				case VK_RIGHT:
					is_move_right = false;
					break;
				default:
					break;
				}
			}
		}

		if (is_move_up) player_position.y -= PLAYER_SPEED;
		if (is_move_down) player_position.y += PLAYER_SPEED;
		if (is_move_left) player_position.x -= PLAYER_SPEED;
		if (is_move_right) player_position.x += PLAYER_SPEED;


		static int counter = 0;
		//每五次循环 动画播放一帧
		if (++counter % 5 == 0) {
			idx_current_anime++;
		}

		idx_current_anime %= PLAYER_ANIME_NUM; //到达动画最后一帧时归零

		cleardevice();
		putimage(0, 0, &img_background); //绘制背景图
		putimage_alpha(player_position.x, player_position.y, &img_player_left[idx_current_anime]); //绘制人物左移动画
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