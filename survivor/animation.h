#pragma once
#include<vector>
#include<graphics.h>


class Animation {
public:
	Animation(LPCTSTR path, int num,int interval) 
	{
		interval_ms = interval;

		TCHAR path_file[256];
		for (size_t i= 0; i < num; i++)
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

	void Play(int x,int y,int delta)
	{

	}

private:
	int timer = 0;   //动画计时器
	int idx_frame = 0;  //动画帧索引
	int interval_ms = 0;
	std::vector<IMAGE*> frame_list;
};
