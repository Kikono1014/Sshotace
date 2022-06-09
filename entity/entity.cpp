#include "../config.h"
#include "../timer/timer.h"
#include "../framework/framework.h"
#include "../gameObject/gameObject.h"
#include "../physic/physic.h"
#include "../scene/scene.h"
#include "../bullet/bullet.h"
#include "./entity.h"

Entity::Entity() :
GameObject()
{
}

Entity::Entity(Framework   &fw,
               SDL_Texture* texture,
               SDL_Rect     hitbox,
               int          type,
               double       healthPoints,
               double       mass,
               double       impact,
               double       angle,
               bool         isPhysical,
               bool         isCollide) :
GameObject(fw,
           texture,
           hitbox,
           GM_Entity,
           mass,
           impact,
           angle,
           isPhysical,
           isCollide)
{
    _enType       = type;
    _healthPoints = healthPoints;
}

int    Entity::getENType      () { return _enType;       }
double Entity::getHealthPoints() { return _healthPoints; }

void Entity::setENType      (int    type        ) { _enType       = type;         }
void Entity::setHealthPoints(double healthPoints) { _healthPoints = healthPoints; }

void Entity::hit(double damage)
{
    _healthPoints -= damage;
}

void Entity::shoot(Framework &fw, Scene &scene, Physic &physic, Bullet bulletT, double x, double y, double shootForce, double distance)
{
    int angle = physic.getAngle(x, y);
    shoot(fw, scene, physic, bulletT, angle, shootForce, distance);
}

void Entity::shoot(Framework &fw, Scene &scene, Physic &physic, Bullet bulletT, int angle, double shootForce, double distance)
{
    double playerCenterX = getX() + getWidth() / 2;
    double shotPointX    = sin(angle * M_PI / 180) * (getWidth() + distance);
    double bulletCenterX = bulletT.getWidth() / 2;

    double bulletX = playerCenterX + shotPointX - bulletCenterX;

    double playerCenterY = getY() + getHeight() / 2;
    double shotPointY    = -cos(angle * M_PI / 180) * getHeight();
    double bulletCenterY = bulletT.getHeight() / 2;

    double bulletY = playerCenterY + shotPointY - bulletCenterY;

    Bullet *bulletP = new Bullet { bulletT };
    bulletP->setX(bulletX);
    bulletP->setY(bulletY);
    bulletP->setAngle(angle);
    physic.moveObj(bulletP, angle, shootForce);
    scene.add(bulletP);
    fw.playSample(0);
}