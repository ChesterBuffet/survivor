#pragma once
#include<graphics.h>


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
	
	//�ƶ�
	void move(ExMessage* msg);
	//���������λ������
	POINT  get_position() {
		return position;
	};
	

};