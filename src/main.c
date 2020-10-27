#include <raycaster.h>
#include <parser.h>

#include <stdlib.h>
#include <ft_string.h>
#include <ft_stdlib.h>

static t_raycaster g_rc = {
	.calc = {
		.playerPosX = INIT_P_POS_X,
		.playerPosY = INIT_P_POS_Y,
		.playerDirX = INIT_P_DIR_X,
		.playerDirY = INIT_P_DIR_Y,
		.planeX = INIT_P_PLANE_X,
		.planeY = INIT_P_PLANE_Y,
		.pitch = 0,
		.posZ = 0
	},
	.key = {
		.up = 0,
		.down = 0,
		.left = 0,
		.right = 0,
		.rot_l = 0,
		.rot_r = 0,
		.rot_up = 0,
		.rot_down = 0
	}
};
#include <ft_stdio/ft_printf.h>

int main(int argc, char **argv) {
	t_sdl	sdl;

	if (argc > 1) {
		if (argv[1] != NULL && ft_strncmp(argv[1], "--width=", 8) == 0) {
			sdl.screenWidth = ft_atoi(argv[1] + 8);
			if (sdl.screenWidth <= 0) {
				sdl.screenWidth = SCREEN_WIDTH;
			}
			g_rc.screenWidth = sdl.screenWidth;
		}
		if (argv[2] != NULL && ft_strncmp(argv[2], "--height=", 9) == 0) {
			sdl.screenHeight = ft_atoi(argv[2] + 9);
			if (sdl.screenHeight <= 0) {
				sdl.screenHeight = SCREEN_HEIGHT;
			}
			g_rc.screenHeight = sdl.screenHeight;
		}
	}
	parser(&g_rc);
	if (initWindow(&sdl) == 1) {
		return EXIT_FAILURE;
	}
	mainLoop(&sdl, &g_rc);
	cleanup(&sdl, &g_rc);
	exit(EXIT_SUCCESS);
}
