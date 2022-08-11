#pragma once
#include "PlacableActor.h"
#include "Player.h"

// M4_Ch4 : Shield powerup needs to provide a delayed invicibility period since multithreading makes the shield effectively useless
class Shield : public PlacableActor
{
public:
    Shield(int x, int y, ActorColor color);
    //~Shield();

    virtual ActorType GetType() override { return ActorType::Shield; }
    virtual void Draw() override;

    void OnCollision(PlacableActor* collidingPlayer) override;
};

