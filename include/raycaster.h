#ifndef RAYCASTER_H
# define RAYCASTER_H

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

# include <sys/types.h>

# define SCREEN_WIDTH	640
# define SCREEN_HEIGHT	480

# define NUMBER_OF_LEVELS	2
# define WALL_TEXTURES		5
# define WEAPON_TEXTURES	3
# define AMMO_TEXTURES		3
# define OBJECT_TEXTURES	4

# define INIT_P_POS_X    22
# define INIT_P_POS_Y    12
# define INIT_P_DIR_X    -1
# define INIT_P_DIR_Y    0
# define INIT_P_PLANE_X  0
# define INIT_P_PLANE_Y  0.66
# define MV_SPEED        0.0110
# define ROT_SPEED       0.0015
# define AMB_LIGHT       5

# define WHITE           0xAAAAAA
# define RED             0xFF0000
# define GREEN           0x00FF00
# define BLUE            0x0000FF
# define BLACK           0x000000

typedef struct	s_sdl {
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*buffer;
	Uint32 			*pixels;
	int 	screenWidth;
	int 	screenHeight;
}				t_sdl;

typedef struct	s_key {
	u_int	up:1;
	u_int	down:1;
	u_int	left:1;
	u_int	right:1;
	u_int	rot_up:1;
	u_int	rot_down:1;
	u_int	rot_l:1;
	u_int	rot_r:1;
	u_int	shoot:1;
	u_int	reload:1;
	u_int	interact:1;
	u_int	item:1;
}				t_key;

typedef struct	s_calc {
	double	playerPosX;
	double	playerPosY;
	double	playerDirX;
	double	playerDirY;
	double	planeX;
	double	planeY;
	double	rayDirX;
	double	rayDirY;
	int 	mapX;
	int 	mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
	int		side;
	int 	drawStart;
	int 	drawEnd;
	double	perpWallDist;
	double	pitch;
	double	posZ;
}				t_calc;

typedef struct	s_level {
	SDL_Texture *wall[WALL_TEXTURES];
	SDL_Texture *weapon[WEAPON_TEXTURES];
	SDL_Texture *ammo[AMMO_TEXTURES];
	SDL_Texture	*grenade;
	SDL_Texture	*health;
	SDL_Texture	*pickup;
	SDL_Texture	*enemy;
	SDL_Texture	*boss;
	SDL_Texture	*objects[OBJECT_TEXTURES];
	SDL_Texture	*door;
	SDL_Texture	*hiddenDoor;
	SDL_Texture	*floor;
	SDL_Texture	*ceiling;
	char		**map;
}				t_level;

typedef struct	s_raycaster {
	int 	screenWidth;
	int 	screenHeight;
	t_level	level[NUMBER_OF_LEVELS];
	t_key	key;
	t_calc	calc;
	double	health;
	double	score;
}				t_raycaster;

int		initWindow(t_sdl *sdl);
void	cleanup(t_sdl *sdl, t_raycaster *rc);
void	mainLoop(t_sdl *sdl, t_raycaster *rc);

#endif