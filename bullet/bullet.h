#ifndef BULLET_H
#define BULLET_H

#include "../gameObject/gameObject.h"

class Bullet : public GameObject
{
private:
    double _damage = 0;
public:
    Bullet();
    Bullet(Framework &fw,
           SDL_Texture* texture,
           SDL_Rect hitbox,
           double mass = 1,
           double impact = 1,
           double angle = 0,
           double damage = 0,
           bool isPhysical = 1,
           bool isCollide = 1);

    double getDamage();

    void   setDamage(double Damage);
};

#endif
