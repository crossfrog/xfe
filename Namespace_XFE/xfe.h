
// "XFE" aka the "CrossFrog Engine", a namespace for making object-oriented 2D games and possibly some other stuff.
//  ^ Get it? Cross?
//
// Written by Leif Johannesson (leif.is.luigi@gmail.com) using SDL. Enjoy it, dammit!

#pragma once

#define SDL_MAIN_HANDLED

#include "SDL.h"
#include <thread>
#include <vector>
#include <string>
#include <unordered_map>

namespace xfe {
	/*x and y for integers.*/
	struct vector2i {
		int x;
		int y;
	};

	/*x and y for floating point.*/
	struct vector2f {
		float x;
		float y;
	};

	/*A struct for RGB values. All hail the Queen's spelling!*/
	struct colour {
		uint8_t r;
		uint8_t g;
		uint8_t b;
	};

	/*The main "engine", updates the current stage on every clock tick using a "while(context.update())" statement.*/
	class context {
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Event* event = new SDL_Event;

		int fps = 60;
		colour background_colour;

		context(
			vector2i windowSize = { 640, 480 },
			const char* windowName = "Untitled XFE Project",
			int FPS = 60,
			colour backgroundColour = colour{ 0, 0, 0 },
			vector2f globalScale = { 1.0, 1.0 }
		);
		bool update();
	private:
		void render(); 
	};

	class actor;
	class stage;

	/*Some form of entity in a stage, contained in an actor section.*/
	class actor {
	public:
		std::string name;
		stage* stage;
		int render_layer;

		/*Called when the actor is created.*/
		virtual void init() {};

		/*Called on every clock tick of its stage.*/
		virtual void update() {};

		/*Called on every clock tick of its stage, sorted in order of the render layer. Equal render layers will be layered incidentally.*/
		virtual void render() {};
	};

	/*Used inside of a stage to partition the actors in sections. This allows for more controlled iteration and is generally handy.*/
	class actor_section {
	public:
		std::vector<actor*> actors;
		std::unordered_map<std::string, xfe::actor*> actor_name_ref;
		xfe::stage* stage;

		std::string name;

		/*Adds the actor to the section, as well as to a dictionary by name. Existing names will be suffixed with a dash ( - ) symbol.*/
		void add_actor_with_name(actor* a);

		/*Adds the actors in the vector to the section, as well as to a dictionary by name. Existing names will be suffixed with a dash ( - ) symbol.*/
		void add_actors_with_names(std::vector<actor*> a_list);

		/*Deletes the actor by the name specifed.*/
		void delete_actor_by_name(std::string name);

		/*Deletes the actors in the vector by their respective names.*/
		void delete_actors_by_name(std::vector<std::string> names);
	};

	/*Encapsulates the actor sections into a "level" that is run by the engine.*/
	class stage {
		context* context;
		std::vector<actor_section*> actor_sections;
	};
};