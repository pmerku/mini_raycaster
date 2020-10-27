#include <raycaster.h>
#include <engine.h>

void movement(t_raycaster *rc) {
	t_key *key = &rc->key;
	t_calc *calc = &rc->calc;

	double      oldDirX;
	double      oldPlaneX;

	if (key->up) {
		if(worldMap[(int)(calc->playerPosX + calc->playerDirX * MV_SPEED)][(int)(calc->playerPosY)] == 0)
			calc->playerPosX += calc->playerDirX * MV_SPEED;
		if(worldMap[(int)(calc->playerPosX)][(int)(calc->playerPosY + calc->playerDirY * MV_SPEED)] == 0)
			calc->playerPosY += calc->playerDirY * MV_SPEED;
	}
	if (key->down) {
		if(worldMap[(int)(calc->playerPosX - calc->playerDirX * MV_SPEED)][(int)(calc->playerPosY)] == 0)
			calc->playerPosX -= calc->playerDirX * MV_SPEED;
		if(worldMap[(int)(calc->playerPosX)][(int)(calc->playerPosY - calc->playerDirY * MV_SPEED)] == 0)
			calc->playerPosY -= calc->playerDirY * MV_SPEED;
	}
	if (key->left) {
//		if (worldMap[(int)(calc->playerPosX - cos(acos(calc->playerDirX) + M_PI) * MV_SPEED)][(int)(calc->playerPosY)] == 0)
//			calc->playerPosX -= cos(acos(calc->playerDirX) + M_PI) * MV_SPEED;
//		if (worldMap[(int)(calc->playerPosX)][(int)(calc->playerPosY + cos(acos(calc->playerDirY) + M_PI) * MV_SPEED)] == 0)
//			calc->playerPosY += cos(acos(calc->playerDirY) + M_PI) * MV_SPEED;
	}
	if (key->right) {
//		if (worldMap[(int)(calc->playerPosX + cos(acos(calc->playerDirX) + M_PI) * MV_SPEED)][(int)(calc->playerPosY)] == 0)
//			calc->playerPosX += cos(acos(calc->playerDirX) + M_PI) * MV_SPEED;
//		if (worldMap[(int)(calc->playerPosX)][(int)(calc->playerPosY - cos(acos(calc->playerDirY) + M_PI) * MV_SPEED)] == 0)
//			calc->playerPosY -= cos(acos(calc->playerDirY) + M_PI) * MV_SPEED;
	}
	if (key->rot_l) {
		oldDirX = calc->playerDirX;
		calc->playerDirX = calc->playerDirX * cos(ROT_SPEED) - calc->playerDirY * sin(ROT_SPEED);
		calc->playerDirY = oldDirX * sin(ROT_SPEED) + calc->playerDirY * cos(ROT_SPEED);
		oldPlaneX = calc->planeX;
		calc->planeX = calc->planeX * cos(ROT_SPEED) - calc->planeY * sin(ROT_SPEED);
		calc->planeY = oldPlaneX * sin(ROT_SPEED) + calc->planeY * cos(ROT_SPEED);
	}
	if (key->rot_r) {
		oldDirX = calc->playerDirX;
		calc->playerDirX = calc->playerDirX * cos(-ROT_SPEED) - calc->playerDirY * sin(-ROT_SPEED);
		calc->playerDirY = oldDirX * sin(-ROT_SPEED) + calc->playerDirY * cos(-ROT_SPEED);
		oldPlaneX = calc->planeX;
		calc->planeX = calc->planeX * cos(-ROT_SPEED) - calc->planeY * sin(-ROT_SPEED);
		calc->planeY = oldPlaneX * sin(-ROT_SPEED) + calc->planeY * cos(-ROT_SPEED);
	}
	if (key->rot_up) {
		// look up
	}
	if (key->rot_down) {
		// look down
	}
}