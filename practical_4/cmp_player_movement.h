#pragma once
#include "cmp_actor_movement.h"
#include <ecm.h>
#include "system_renderer.h"

class PlayerMovementComponent : public ActorMovementComponent
{
protected:
	//std::vector<std::shared_ptr<sf::Keyboard::Key>> _controls[4];
	float _xdirection = 0.0f;
	float _ydirection = 0.0f;
public:
	explicit PlayerMovementComponent(Entity* p);
	PlayerMovementComponent() = delete;

	//std::vector<std::shared_ptr<sf::Keyboard>> getKeys();
	//void setKeys(std::vector<std::shared_ptr<sf::Keyboard::Key>> controls[4]);
	//void validKey();
	void setDirection(float &xdirection, float &ydirection);
	float getXDirection();
	float getYDirection();
	void render() override {}
	void update(double dt) override;

	//template for mapping keys
	/*template <typename T, typename... Targs>
	std::shared_ptr<T> addKey(Targs... params)
	{
		static_assert(std::is_base_of<sf::Keyboard, T>::value, "must be a key");
		std::shared_ptr<T> sp(std::make_shared<T>(this, params ...));
		_controls.push_back(sp);
		return sp;
	}*/

};