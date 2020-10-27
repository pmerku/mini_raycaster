#ifndef ENGINE_H
# define ENGINE_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_thread.h>
# include <SDL2/SDL_image.h>

# include <stdlib.h>
# include <ft_stdio/ft_printf.h>
# include <unistd.h>
# include <raycaster.h>
# include <math.h>

# define mapWidth 24
# define mapHeight 24

extern int worldMap[mapWidth][mapHeight];

void render(t_sdl *sdl, t_raycaster *rc);
void movement(t_raycaster *rc);

SDL_Color     convertColor(unsigned int hexa_value);
SDL_Color     selectWallColor(int map_x, int map_y);
SDL_Color     applyNightEffect(SDL_Color color, double distance);

#endif