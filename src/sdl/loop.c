#include <raycaster.h>
#include <engine.h>



SDL_bool keyPress(SDL_KeyboardEvent *event, t_raycaster *rc) {
	t_key *key = &rc->key;

	if (event->keysym.scancode == SDL_SCANCODE_ESCAPE) {
		return SDL_FALSE;
	}
	if (event->keysym.scancode == SDL_SCANCODE_W) {
		key->up = 1;
	}
	if (event->keysym.scancode == SDL_SCANCODE_S) {
		key->down = 1;
	}
	if (event->keysym.scancode == SDL_SCANCODE_A) {
		key->left = 1;
	}
	if (event->keysym.scancode == SDL_SCANCODE_D) {
		key->right = 1;
	}
	if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
		key->rot_l = 1;
	}
	if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
		key->rot_r = 1;
	}
	if (event->keysym.scancode == SDL_SCANCODE_UP) {
		key->rot_up = 1;
	}
	if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
		key->rot_down = 1;
	}
	return SDL_TRUE;
}

SDL_bool keyRelease(SDL_KeyboardEvent *event, t_raycaster *rc) {
	t_key *key = &rc->key;

	if (event->keysym.scancode == SDL_SCANCODE_W) {
		key->up = 0;
	}
	if (event->keysym.scancode == SDL_SCANCODE_S) {
		key->down = 0;
	}
	if (event->keysym.scancode == SDL_SCANCODE_A) {
		key->left = 0;
	}
	if (event->keysym.scancode == SDL_SCANCODE_D) {
		key->right = 0;
	}
	if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
		key->rot_l = 0;
	}
	if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
		key->rot_r = 0;
	}
	if (event->keysym.scancode == SDL_SCANCODE_UP) {
		key->rot_up = 0;
	}
	if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
		key->rot_down = 0;
	}
	return SDL_TRUE;
}

void mousePress(SDL_MouseButtonEvent *event, t_raycaster *rc) {
	t_key *key = &rc->key;
	if (event->button == SDL_BUTTON_LEFT) {
		key->shoot = 1;
	}
}

void mouseRelease(SDL_MouseButtonEvent *event, t_raycaster *rc) {
	t_key *key = &rc->key;
	if (event->button == SDL_BUTTON_LEFT) {
		key->shoot = 0;
	}
}

void mouseMotion(SDL_MouseMotionEvent *event, t_raycaster *rc) {
	if (event->x > 0 && event->x < rc->screenWidth / 2) {
		// look left
	}
	else if (event->x < rc->screenWidth && event->x > rc->screenWidth / 2) {
		// look right
	}
}

void mouseWheel(SDL_MouseWheelEvent *event) {
	if (event->x == 1) {
		// next weapon
	}
	else if (event->x == -1) {
		// prev weapon
	}
}

void mainLoop(t_sdl *sdl, t_raycaster *rc) {
	//Event handler
	SDL_Event event;
	SDL_bool loop = SDL_TRUE;
	while (loop) {
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
				case SDL_QUIT:
					loop = SDL_FALSE;
					break;
				case SDL_KEYDOWN:
					loop = keyPress(&event.key, rc);
					break;
				case SDL_KEYUP:
					keyRelease(&event.key, rc);
					break;
				case SDL_MOUSEBUTTONDOWN:
					mousePress(&event.button, rc);
					break;
				case SDL_MOUSEBUTTONUP:
					mouseRelease(&event.button, rc);
					break;
				case SDL_MOUSEMOTION:
					mouseMotion(&event.motion, rc);
					break;
				case SDL_MOUSEWHEEL:
					mouseWheel(&event.wheel);
					break;
				default:
					break;
			}
		}
		//Clear screen
		SDL_SetRenderDrawColor(sdl->renderer, 0xAA, 0x90, 0x90, 0xFF);
		SDL_RenderClear(sdl->renderer);

		movement(rc);
		render(sdl, rc);

		SDL_UpdateTexture(sdl->buffer, NULL, sdl->pixels, sdl->screenWidth * sizeof(Uint32));
		SDL_SetRenderTarget(sdl->renderer, NULL);
		SDL_RenderCopy(sdl->renderer, sdl->buffer, NULL, NULL);

		//Update screen
		SDL_RenderPresent(sdl->renderer);
	}
}
