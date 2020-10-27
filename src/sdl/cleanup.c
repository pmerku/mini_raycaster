#include <raycaster.h>
#include <ft_memory.h>

void cleanup(t_sdl *sdl, t_raycaster *rc) {
	//Free pixels buffer
	if (sdl->pixels) {
		ft_free(sdl->pixels);
	}
	sdl->pixels = NULL;

	//Free texture buffer
	if (sdl->buffer) {
		SDL_DestroyTexture(sdl->buffer);
	}
	sdl->buffer = NULL;

	//Destroy window
	if (sdl->renderer) {
		SDL_DestroyRenderer(sdl->renderer);
	}
	if (sdl->window) {
		SDL_DestroyWindow(sdl->window);
	}
	sdl->renderer = NULL;
	sdl->window = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
