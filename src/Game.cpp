#include <cwchar>
#include <thread>
#include "Game.hpp"
#include "utils/Cleanup.hpp"
#include "entities/definition/EntityDB.hpp"
#include "entities/PlayerEntity.hpp"
#include "entities/bases/BaseEntity.hpp"
#include "input/InputSystem.hpp"

namespace chrono = std::chrono;
using timestamp = decltype(chrono::steady_clock::now());

Game::Game() {
	this->renderer = std::make_unique<render::Renderer>(90, 25);
	this->input_system = &input::InputSystem::instance();
}

void Game::start_loop() {
	if (this->running) return;
	this->running = true;

	this->init();
	this->main_loop();
}

void Game::stop_loop() {
	if (!this->running) return;
	this->running = false;
}

void Game::init() {
	Scene* s = new Scene();
	s->attach_entity(ENTITY_CREATE(entities::PlayerEntity, player));
	this->current_scene = s;
}

void Game::end() {
}

void Game::main_loop() {
	timestamp last_frame = chrono::steady_clock::now();
	constexpr const uint8_t max_fps = 60;

	while (this->running) {
		const timestamp current_frame = chrono::steady_clock::now();

		float delta = duration_cast<chrono::duration<float>>(current_frame - last_frame).count();
		last_frame = current_frame;

		this->tick(delta);
		this->render();
		this->input_system->reset_key_buff();

		// cap fps
		if (delta < 1.0f / max_fps) {
			std::this_thread::sleep_for(chrono::duration<float>(1.0f / max_fps - delta));
		}
	}

	this->end();
}


void Game::tick(float delta) {
	if (this->current_scene)
		this->current_scene->tick(delta);
}

void Game::render() {
	this->renderer->clear_buffer();

	if (this->current_scene) {
		this->current_scene->render(this->renderer->get_render_utils());
	}

	this->renderer->push_buffer();
}