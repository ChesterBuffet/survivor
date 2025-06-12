#pragma once
#include<graphics.h>
#include<math.h>
#include"main.h"


class Player
{

private:
	POINT position = { 600 ,300 };
	int speed = 5;
	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;

public:
	
	//移动
	void move(ExMessage* msg);
	//返回人物的位置坐标
	POINT  get_position() {

		POINT p = position;
		return p;
	};

	int  left_right() 
	{
		return (is_move_left - is_move_right);
	}
	

};