#ifndef PLAYER_H
#define PLAYER_H

#include "../entity/entity.h"

class Player : public Entity
{
private:
    double _moveForce = 0;
    double _jumpForce = 0;
public:
    Player();
    Player(Framework   &fw,
           SDL_Texture* texture,
           SDL_Rect     hitbox,
           double       moveForce    = 0,
           double       jumpForce    = 0,
           double       healthPoints = 1,
           double       mass         = 1,
           double       impact       = 1,
           double       angle        = 0,
           bool         isPhysical   = 0,
           bool         isCollide    = 0);

    double getMoveForce();
    double getJumpForce();

    void   setMoveForce(double moveForce);
    void   setJumpForce(double jumpForce);
};

#endif
