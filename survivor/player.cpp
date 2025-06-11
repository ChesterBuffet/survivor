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

	if (is_move_up)    position.y -= speed;
	if (is_move_down)  position.y += speed;
	if (is_move_left)  position.x -= speed;
	if (is_move_right) position.x += speed;
}