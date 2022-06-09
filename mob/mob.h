#ifndef MOB_H
#define MOB_H

#include "../entity/entity.h"

class Mob : public Entity
{
private:
    void (*_script)(Framework &fw, Scene &scene, Physic &physic, Mob *mob) = {};
public:
    Mob();
    Mob(Framework   &fw,
        SDL_Texture* texture,
        SDL_Rect     hitbox,
        void       (*script)(Framework &fw, Scene &scene, Physic &physic, Mob *mob) = {},
        double       healthPoints = 1,
        double       mass         = 1,
        double       impact       = 1,
        double       angle        = 0,
        bool         isPhysical   = 0,
        bool         isCollide    = 0);

    void setScript(void (*script)(Framework &fw, Scene &scene, Physic &physic, Mob *mob));

    void doScript(Framework &fw, Scene &scene, Physic &physic, Mob *mob);
};

#endif
