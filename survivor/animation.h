#pragma once
#include<vector>
#include<graphics.h>
#include<string>
#include"putimage_alpha.h"

class Animation {
public:
	Animation(LPCTSTR path, int num, int interval)
	{
		interval_ms = interval;  

		TCHAR path_file[256];
		for (size_t i = 0; i < num; i++)
		{
			_stprintf_s(path_file, path, i);
			IMAGE* frame = new IMAGE();
			loadimage(frame, path_file);
			frame_list.push_back(frame);
		}

	}
	~Animation() {
		for (size_t i = 0; i < frame_list.size(); i++)
		{
			delete frame_list[i];
		}
	}

	//定时绘制动画
	void play(int x, int y, int delta)
	{
		timer += delta;
		if (timer >= interval_ms)
		{
			idx_frame = (idx_frame + 1) % frame_list.size();
			timer = 0;
		}
		putimage_alpha(x, y, frame_list[idx_frame]);
	}


	////加载角色的左移和右移动画
	//void load_animation()
	//{
	//	for (SIZE_T i = 0; i < PLAYER_ANIME_NUM; i++) {
	//		//分别将左移和右移动画装入数组
	//		std::wstring path = L"img/player_left_" + std::to_wstring(i) + L".png";
	//		loadimage(&img_player_left[i], path.c_str());
	//		path = L"img/player_right_" + std::to_wstring(i) + L".png";
	//		loadimage(&img_player_right[i], path.c_str());
	//	}
	//}










private:
	int timer = 0;   //动画计时器
	int idx_frame = 0;  //动画帧索引
	int interval_ms = 0;  //动画帧间隔时间
	std::vector<IMAGE*> frame_list;
	static const int PLAYER_ANIME_NUM = 6;   //玩家动画动作帧总数



	/*IMAGE  img_player_left[PLAYER_ANIME_NUM];
	IMAGE  img_player_right[PLAYER_ANIME_NUM];*/
	
};







