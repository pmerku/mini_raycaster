#include <raycaster.h>
#include <ft_stdio/ft_printf.h>
#include <unistd.h>
#include <ft_memory.h>

int initWindow(t_sdl *sdl) {
	if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
		ft_fprintf(STDERR_FILENO, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	//Create window
	sdl->window = SDL_CreateWindow("Mini Raycaster", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sdl->screenWidth, sdl->screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (sdl->window == NULL) {
		ft_fprintf(STDERR_FILENO, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	//Create renderer for window
	sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);
	if (sdl->renderer == NULL) {
		ft_fprintf(STDERR_FILENO, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	//Create texture buffer
	sdl->buffer = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, sdl->screenWidth, sdl->screenHeight);
	if (sdl->buffer == NULL) {
		ft_fprintf(STDERR_FILENO, "Texture buffer could not be created! SDL Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	SDL_SetRenderTarget(sdl->renderer, sdl->buffer);
	SDL_SetRenderDrawColor(sdl->renderer, 0x00, 255, 0x00, 0x00);

	sdl->pixels = ft_calloc(sizeof(Uint32), (sdl->screenHeight * sdl->screenWidth));
	if (sdl->pixels == NULL) {
		ft_fprintf(STDERR_FILENO, "Pixels buffer could not be created! Malloc Error\n");
		return EXIT_FAILURE;
	}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags)) {
		ft_fprintf(STDERR_FILENO, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
