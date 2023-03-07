#pragma once
#include "Solver.hpp"

class Renderer {
	public:
		Renderer(sf::RenderTarget& render_target) : target{render_target} {  }

		void render(const Solver& solver) const {

			sf::CircleShape circle(1.f);
			circle.setPointCount(32);
			circle.setOrigin(1.0f, 1.0f);
			circle.setPointCount(20);
			auto& objects_vector = solver.getObjects();
			for (const auto& object : objects_vector) {
				circle.setPosition(object.position);
				circle.setScale(object.radius, object.radius);
				circle.setFillColor(object.color);
				target.draw(circle);
			}
		}


	private:
		sf::RenderTarget& target;
};