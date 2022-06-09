#ifndef ENTITY_H
#define ENTITY_H

#include "../gameObject/gameObject.h"

enum EtityTypes
{   
    EN_Base,
    EN_Mob,
    EN_Player
};

class Entity : public GameObject
{
private:
    int    _enType       = EN_Base;
    double _healthPoints = 1;
public:
    Entity();
    Entity( Framework   &fw,
            SDL_Texture* texture,
            SDL_Rect     hitbox,
            int          type         = EN_Base,
            double       healthPoints = 1,
            double       mass         = 1,
            double       impact       = 1,
            double       angle        = 0,
            bool         isPhysical   = 0,
            bool         isCollide    = 0);

    int    getENType      ();
    double getHealthPoints();

    void setENType      (int type);
    void setHealthPoints(double healthPoints);

    void hit(double damage);
    void shoot(Framework &fw, Scene &scene, Physic &physic, Bullet bulletT, double x, double y, double shootForce, double distance);
    void shoot(Framework &fw, Scene &scene, Physic &physic, Bullet bulletT, int angle, double shootForce, double distance);
};

#endif
