#include "../config.h"
#include "../timer/timer.h"
#include "../framework/framework.h"
#include "../gameObject/gameObject.h"
#include "../physic/physic.h"
#include "../scene/scene.h"
#include "../bullet/bullet.h"
#include "../entity/entity.h"
#include "./player.h"

Player::Player() :
Entity()
{
}

Player::Player(Framework   &fw,
               SDL_Texture* texture,
               SDL_Rect     hitbox,
               double       moveForce,
               double       jumpForce,
               double       healthPoints,
               double       mass,
               double       impact,
               double       angle,
               bool         isPhysical,
               bool         isCollide) :
Entity( fw,
        texture,
        hitbox,
        EN_Player,
        healthPoints,
        mass,
        impact,
        angle,
        isPhysical,
        isCollide)
{
    _moveForce = moveForce;
    _jumpForce = jumpForce;
}


double Player::getMoveForce() { return _moveForce; }
double Player::getJumpForce() { return _jumpForce; }

void   Player::setMoveForce(double moveForce) { _moveForce = moveForce; }
void   Player::setJumpForce(double jumpForce) { _jumpForce = jumpForce; }
