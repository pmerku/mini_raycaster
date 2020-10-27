#include <raycaster.h>
#include <ft_stdio/ft_printf.h>
#include <unistd.h>

SDL_Texture* loadTexture(t_sdl *sdl, char *path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else {
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(sdl->renderer, loadedSurface);
		if(newTexture == NULL) {
			printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

int	loadMedia(t_sdl *sdl, t_raycaster *rc) {
	t_level *level = &rc->level[0];

	//Load PNG texture
	if ((level->door = loadTexture(sdl, "path")) == NULL ) {
		ft_fprintf(STDERR_FILENO, "Failed to load texture image!\n" );
		return 1;
	}

	return 0;
}