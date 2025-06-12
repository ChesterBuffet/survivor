#include"player.h"


void Player::move(ExMessage* msg) {
	while (peekmessage(msg)) {

		if ((*msg).message == WM_KEYDOWN) {
			switch ((*msg).vkcode) {
			case VK_UP:
				is_move_up = true;
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
		else if ((*msg).message == WM_KEYUP)
		{
			switch ((*msg).vkcode) {
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

	//利用单位向量 确保移动距离相同
	int dir_x = is_move_right - is_move_left;
	int dir_y = is_move_down - is_move_up;
	double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
	if (len_dir != 0) {
		double normalized_x = dir_x / len_dir;
		double normalized_y = dir_y / len_dir;
		position.x += (int)(speed * normalized_x);
		position.y += (int)(speed * normalized_y);
	}
	if (position.x < 0) position.x = 0;
	if (position.y < 0) position.y = 0;
	if (position.x+ PLAYER_WIDTH> WINDOWS_WIDTH) 
		position.x = WINDOWS_WIDTH- PLAYER_WIDTH;
	if (position.y + PLAYER_HEIGHT > WINDOWS_HEIGHT) 
		position.y = WINDOWS_HEIGHT - PLAYER_HEIGHT;

	//if (is_move_up)    position.y -= speed;
	//if (is_move_down)  position.y += speed;
	//if (is_move_left)  position.x -= speed;
	//if (is_move_right) position.x += speed;
}