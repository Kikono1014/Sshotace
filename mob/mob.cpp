#include "../config.h"
#include "../timer/timer.h"
#include "../framework/framework.h"
#include "../gameObject/gameObject.h"
#include "../physic/physic.h"
#include "../scene/scene.h"
#include "../bullet/bullet.h"
#include "../entity/entity.h"
#include "./mob.h"

Mob::Mob() :
Entity()
{
}

Mob::Mob(Framework   &fw,
         SDL_Texture* texture,
         SDL_Rect     hitbox,
         void       (*script)(Framework &fw, Scene &scene, Physic &physic, Mob *mob),
         double       healthPoints,
         double       mass,
         double       impact,
         double       angle,
         bool         isPhysical,
         bool         isCollide) :
Entity( fw,
        texture,
        hitbox,
        EN_Mob,
        healthPoints,
        mass,
        impact,
        angle,
        isPhysical,
        isCollide)
{
    _script = script;
}

void Mob::setScript(void (*script)(Framework &fw, Scene &scene, Physic &physic, Mob *mob)) { _script = script; }

void Mob::doScript(Framework &fw, Scene &scene, Physic &physic, Mob *mob)
{
    (*_script)(fw, scene, physic, mob);
}
