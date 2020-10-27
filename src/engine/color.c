# include <raycaster.h>
# include <engine.h>

SDL_Color     convertColor(unsigned int hexa_value)
{
	SDL_Color   color;

	color.r = ((hexa_value >> 16U) & (unsigned int)0xFF);
	color.g = ((hexa_value >> 8U) & (unsigned int)0xFF);
	color.b = ((hexa_value) & (unsigned int)0xFF);
	return (color);
}

SDL_Color     selectWallColor(int map_x, int map_y)
{
	SDL_Color   color;

	if (worldMap[map_x][map_y] == 1)
		color = convertColor(RED);
	else if (worldMap[map_x][map_y] == 2)
		color = convertColor(GREEN);
	else if (worldMap[map_x][map_y] == 3)
		color = convertColor(BLUE);
	else if (worldMap[map_x][map_y] == 4)
		color = convertColor(WHITE);
	else
		color = convertColor(BLACK);
	return (color);
}

SDL_Color     applyNightEffect(SDL_Color color, double distance)
{
	if (color.r / distance * AMB_LIGHT <= color.r)
		color.r = color.r / distance * AMB_LIGHT;
	if (color.g / distance * AMB_LIGHT <= color.g)
		color.g = color.g / distance * AMB_LIGHT;
	if (color.b / distance * AMB_LIGHT <= color.b)
		color.b = color.b / distance * AMB_LIGHT;
	return (color);
}
