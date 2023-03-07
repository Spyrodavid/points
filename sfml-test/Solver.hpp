#pragma once
#include <vector>
#include <iostream>


struct VerletObject {
	sf::Vector2f position;
	sf::Vector2f position_last;
	sf::Vector2f acceleration;
	float radius = 10.f;
	sf::Color color = sf::Color::White;

	VerletObject() = default;
	VerletObject(sf::Vector2f position_, float radius_) {
		position = position_;
		position_last = position_;
		radius = radius_;
	}

	void update(float dt) {
		const sf::Vector2f displacement = position - position_last;
		// Update position
		position_last = position;
		position = position + displacement + acceleration * (dt * dt);
		// Reset acceleration
		acceleration = {};
	}

	void accelerate(sf::Vector2f acceleration_) {
		acceleration = acceleration_;
	}
	
};

class Solver {
	public:
		Solver() = default;

		float dt = .005;

		void update() {
			applyGravity();
			updateObjects(dt);
			checkCollisions();
		}

		void applyGravity() {
			for (auto& object : object_vector) {
				sf::Vector2f difference = gravitational_center - object.position;
				float distance = sqrt(difference.x * difference.x + difference.y * difference.y);
				if (distance > 0) {
					object.accelerate((difference / distance) * gravity_value);
				}
			}
		}


		VerletObject& makeObject(sf::Vector2f position, float radius) {
			VerletObject new_object{position, radius};
			
			object_vector.emplace_back(new_object);

			return object_vector.at(object_vector.size() - 1);
		}

		const std::vector<VerletObject>& getObjects() const
		{
			return object_vector;
		}

		int getObjectCount() const {
			return object_vector.size();
		}

		void setGravityCenter(sf::Vector2f position) {
			gravitational_center.x = position.x;
			gravitational_center.y = position.y;
		}

		void setGravityValue(float gravity) {
			gravity_value = gravity;
		}

		float getGravityValue() {
			return gravity_value;
		}
		

	private:
		std::vector<VerletObject> object_vector;
		sf::Vector2f gravitational_center;
		float gravity_value = 100.f;

		void updateObjects(float dt) {
			for (auto& object : object_vector) {
				object.update(dt);
			}
		}

		void checkCollisions() {
			for (auto& object_1 : object_vector) {
				for (auto& object_2 : object_vector) {
					if (&object_1 == &object_2) {
						continue;
					}
					sf::Vector2f difference = object_2.position - object_1.position;
					float distance = sqrt(difference.x * difference.x + difference.y * difference.y);
					sf::Vector2f unit_vector12 = difference / distance;

					
					if (distance < object_1.radius + object_2.radius) {
						float needed_move = (object_1.radius + object_2.radius) - distance;
						
						object_1.position -= unit_vector12 * needed_move * .5f;
						object_2.position += unit_vector12 * needed_move * .5f;
					}
				}
			}
		}
};