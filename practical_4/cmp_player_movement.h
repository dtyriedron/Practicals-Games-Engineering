#pragma once
#include "cmp_actor_movement.h"
#include <ecm.h>
#include "system_renderer.h"

class PlayerMovementComponent : public ActorMovementComponent
{
protected:
	std::vector<std::shared_ptr<sf::Keyboard>> _controls[4];
public:
	explicit PlayerMovementComponent(ActorMovementComponent* p);
	PlayerMovementComponent() = delete;

	void getKey();
	void setKey();
	void validKey();

	void render() override {}
	void update(double dt) override;

	//template for mapping keys
	template <typename T, typename... Targs>
	std::shared_ptr<T> addKey(Targs... params)
	{
		static_assert(std::is_base_of<sf::Keyboard, T>::value, "must be a key");
		std::shared_ptr<T> sp(std::make_shared<T>(this, params ...));
		_controls.push_back(sp);
		return sp;
	}

};