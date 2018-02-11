#pragma once
#include "cmp_actor_movement.h"

class AiMovementComponent : public ActorMovementComponent
{
protected:
	float _xdirection = 0.0f;
	float _ydirection = 0.0f;
public:
	explicit AiMovementComponent(Entity* p);
	AiMovementComponent() = delete;

	void setDirection(float &xdirection, float &ydirection);
	float getXDirection();
	float getYDirection();

	void render() override {}
	void update(double dt) override;
};