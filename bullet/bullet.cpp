#include "../config.h"
#include "../timer/timer.h"
#include "../framework/framework.h"
#include "../gameObject/gameObject.h"
#include "../physic/physic.h"
#include "../scene/scene.h"
#include "./bullet.h"

Bullet::Bullet() :
GameObject()
{
}

Bullet::Bullet(Framework &fw,
               SDL_Texture* texture,
               SDL_Rect hitbox,
               double mass,
               double impact,
               double angle,
               double damage,
               bool isPhysical,
               bool isCollide) :
GameObject(fw,
           texture,
           hitbox,
           GM_Bullet,
           mass,
           impact,
           angle,
           isPhysical,
           isCollide)
{
    _damage = damage;
}


double Bullet::getDamage() { return _damage; }

void   Bullet::setDamage(double damage) { _damage = damage; }
