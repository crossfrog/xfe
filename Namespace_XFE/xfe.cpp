#include "xfe.h"

//xfe::actor_section

void xfe::actor_section::add_actor_with_name(actor* a) {
	this->actors.push_back(a);
	while (actor_name_ref.find(a->name) != actor_name_ref.end()) {
		a->name += "-";
	}

	this->actor_name_ref[a->name] = a;
}

void xfe::actor_section::add_actors_with_names(std::vector<actor*> a_list) {
	for (auto i : a_list) {
		add_actor_with_name(i);
	}
}

void xfe::actor_section::delete_actor_by_name(std::string name) {
	actor* a = actor_name_ref[name];
	actor_name_ref.erase(name);
	delete a;
}

void xfe::actor_section::delete_actors_by_name(std::vector<std::string> names) {
	for (auto i : names) {
		delete_actor_by_name(i);
	}
}

// xfe::context

xfe::context::context(vector2i windowSize, const char* windowName, int FPS, colour backgroundColour, vector2f globalScale) {
	SDL_Init(SDL_INIT_EVERYTHING);

	this->window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize.x * globalScale.x, windowSize.y, 0);
	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	this->fps = fps;
	this->background_colour = backgroundColour;
}

bool xfe::context::update() {
	while (event->type != SDL_QUIT) {
		while (SDL_PollEvent(event)) {}

		render();

		return 1;
	}
	SDL_DestroyWindow(window);
	SDL_Quit;
	return 0;
}

void xfe::context::render() {
	SDL_SetRenderDrawColor(renderer, background_colour.r, background_colour.g, background_colour.b, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}