#include <engine.h>
#include <raycaster.h>

int worldMap[mapWidth][mapHeight]=
{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	calcInit(t_raycaster *rc, int x) {
	t_calc	*calc = &rc->calc;

	double camera_x = 2 * x / (double)(rc->screenWidth) - 1;
	calc->rayDirX = calc->playerDirX + calc->planeX * camera_x;
	calc->rayDirY = calc->playerDirY + calc->planeY * camera_x;
	calc->mapX = (int)(calc->playerPosX);
	calc->mapY = (int)(calc->playerPosY);
	calc->deltaDistX = sqrt(1 + pow(calc->rayDirY, 2) / pow(calc->rayDirX, 2));
	calc->deltaDistY = sqrt(1 + pow(calc->rayDirX, 2) / pow(calc->rayDirY, 2));
	if (calc->rayDirX < 0)
	{
		calc->stepX = -1;
		calc->sideDistX = (calc->playerPosX - calc->mapX) * calc->deltaDistX;
	}
	else
	{
		calc->stepX = 1;
		calc->sideDistX = (calc->mapX + 1.0 - calc->playerPosX) * calc->deltaDistX;
	}
	if (calc->rayDirY < 0)
	{
		calc->stepY = -1;
		calc->sideDistY = (calc->playerPosY - calc->mapY) * calc->deltaDistY;
	}
	else
	{
		calc->stepY = 1;
		calc->sideDistY = (calc->mapY + 1.0 - calc->playerPosY) * calc->deltaDistY;
	}
}

int	mapCheck(t_raycaster *rc, int x, int y) {
	t_calc *calc = &rc->calc;

	if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight || worldMap[calc->mapX][calc->mapY] > 0)
		return 1;
	else
		return 0;
}

void performDDA(t_raycaster *rc) {
	t_calc *calc = &rc->calc;
	int hit = 0;

	while (hit == 0) {
		if (calc->sideDistX < calc->sideDistY) {
			calc->sideDistX += calc->deltaDistX;
			calc->mapX += calc->stepX;
			calc->side = 0;
		}
		else {
			calc->sideDistY += calc->deltaDistY;
			calc->mapY += calc->stepY;
			calc->side = 1;
		}
		hit = mapCheck(rc, calc->mapX, calc->mapY);
	}
}

void calcWall(t_raycaster *rc) {
	t_calc	*calc = &rc->calc;

	if (calc->side == 0) {
		calc->perpWallDist = (calc->mapX - calc->playerPosX + (1 - calc->stepX) / 2) / calc->rayDirX;
	}
	else {
		calc->perpWallDist = (calc->mapY - calc->playerPosY + (1 - calc->stepY) / 2) / calc->rayDirY;
	}
	int lineHeight = (int)(rc->screenHeight / calc->perpWallDist);
	calc->drawStart = -lineHeight / 2 + rc->screenHeight / 2 + calc->pitch + (calc->posZ / calc->perpWallDist);
	if (calc->drawStart < 0) {
		calc->drawStart = 0;
	}
	calc->drawEnd = lineHeight / 2 + rc->screenHeight / 2 + calc->pitch + (calc->posZ / calc->perpWallDist);
	if (calc->drawEnd >= rc->screenHeight) {
		calc->drawEnd = rc->screenHeight - 1;
	}
}

Uint32 rgbToInt(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16) + (g << 8) + b;
}

void drawPixel(t_sdl *sdl, int x, int y, uint32_t color) {
	if (x < 0 || y < 0 || x >= sdl->screenWidth || y >= sdl->screenHeight)
		return;
	sdl->pixels[(x + y * sdl->screenWidth)] = color;
}

void drawLine(t_sdl *sdl, t_raycaster *rc, int x) {
	t_calc *calc = &rc->calc;

//	double wallX;
//	if (calc->side == 0) {
//		wallX = calc->playerPosY + calc->perpWallDist * calc->rayDirY;
//	}
//	else {
//		wallX = calc->playerPosX + calc->perpWallDist * calc->rayDirX;
//	}
//	wallX -= floor(wallX);
//	int texX = (int)(wallX * (double)64) % 64;
//
	SDL_Color color = applyNightEffect(selectWallColor(calc->mapX, calc->mapY), calc->perpWallDist);
	if (calc->side == 1) {
		color.r /= 2;
		color.g /= 2;
		color.b /= 2;
	}

	for (int j = 0; j < calc->drawStart; j++) {
		drawPixel(sdl, x, j, rgbToInt(0xAA, 0xBB, 0xCC));
	}
	for (int j = calc->drawStart; j < calc->drawEnd; j++) {
		drawPixel(sdl, x, j, rgbToInt(color.r, color.g, color.b));
	}
	for (int j = calc->drawEnd; j < rc->screenHeight; j++) {
		drawPixel(sdl, x, j, rgbToInt(0xCC, 0xBB, 0xAA));
	}
}

void render(t_sdl *sdl, t_raycaster *rc) {
//	drawBackground();
//	calcSpriteDistance();
	for (int x = 0; x < rc->screenWidth; x++) {
		calcInit(rc, x);
		performDDA(rc);
		calcWall(rc);
		drawLine(sdl, rc, x);
	}
//	drawSprite();
//	drawHud();
}