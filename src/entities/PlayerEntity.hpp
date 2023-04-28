#pragma once

#include <iostream>
#include "bases/BaseEntity.hpp"
#include "../utils/Point.hpp"
#include "bases/BaseHealthEntity.hpp"

namespace entities {

	class PlayerEntity : public BaseHealthEntity {
	DEFINE_ENTITY_CLASS(player)

		std::string player_name;
		render::Color player_color = render::default_colors::WHITE;

	public:
		PlayerEntity() {
			this->position = {5, 5};
			this->velocity = {20, 8};
		}

		void render(render::render_helpers::RenderUtils&& renderer) const override;
		void tick(float delta) override;
	};


	DEFINE_ENTITY_FACTORY(PlayerEntity)
}