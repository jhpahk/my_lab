#include <iostream>

class Detector {
public:

	int map_checked[15][15];
	bool map_can_go[15][15];
	char ex_check_dir;

	bool can_go_outside(int map[15][15], int x, int y, bool wall[4]) {	// °¤Çû´ÂÁö ÆÇ´Ü (º® Á¦¿Ü)
		if (map_checked[y][x] == 1) {
			return map_can_go[y][x];
		}
		if ((y == 0 && !wall[0]) || (y == 14 && !wall[1]) || (x == 0 && !wall[2]) || (x == 14 && !wall[3])) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = true;
			return true;
		}
		else if (y == 0 || y == 14 || x == 0 || x == 14) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = false;
			return false;
		}
		/*
		if (x == p_x && y == p_y) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = false;
			return false;
		}
		*/
		map_checked[y][x] = 1;
		map_can_go[y][x] = false;

		bool go_up = true;
		bool go_down = true;
		bool go_left = true;
		bool go_right = true;


		if ((y > 0 && map[y - 1][x] != 0)/* || (x == p_x && y - 1 == p_y)*/) {
			go_up = false;
		}
		else {
			if (ex_check_dir != 'U') {
				ex_check_dir = 'D';
				go_up = can_go_outside(map, x, y - 1, wall);
			}
			else {
				go_up = false;
			}
		}

		if (go_up) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = true;
			return true;
		}


		if ((y < 14 && map[y + 1][x] != 0)/* || (x == p_x && y + 1 == p_y)*/) {
			go_down = false;
		}
		else {
			if (ex_check_dir != 'D') {
				ex_check_dir = 'U';
				go_down = can_go_outside(map, x, y + 1, wall);
			}
			else {
				go_down = false;
			}
		}

		if (go_down) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = true;
			return true;
		}


		if ((x > 0 && map[y][x - 1] != 0)/* || (x - 1 == p_x && y == p_y)*/) {
			go_left = false;
		}
		else {
			if (ex_check_dir != 'L') {
				ex_check_dir = 'R';
				go_left = can_go_outside(map, x - 1, y, wall);
			}
			else {
				go_left = false;
			}
		}

		if (go_left) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = true;
			return true;
		}


		if ((x < 14 && map[y][x + 1] != 0)/* || (x + 1 == p_x && y == p_y)*/) {
			go_right = false;
		}
		else {
			if (ex_check_dir != 'R') {
				ex_check_dir = 'L';
				go_right = can_go_outside(map, x + 1, y, wall);
			}
			else {
				go_right = false;
			}
		}

		if (go_right) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = true;
			return true;
		}

		if (!go_up && !go_down && !go_left && !go_right) {
			return false;
		}
		else {
			map_checked[y][x] = 1;
			map_can_go[y][x] = true;
			return true;
		}
	}
};

int main() {
	int map[15][15] = {
		{0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 0, 1, 1, 0, 0},
		{2, 0, 0, 2, 0, 0, 0, 2, 0, 1, 1, 0, 1, 0, 0},
		{2, 0, 2, 2, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
		{2, 2, 2, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0} };

	Detector detect;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			detect.map_checked[j][i] = 0;
		}
	}

	bool wall[4] = { true, false, false, true };

	std::cout << std::boolalpha << detect.can_go_outside(map, 4, 8, wall) << std::endl;
}