#ifndef GAMEOBJ_H
#define GAMEOBJ_H

enum GameObjectTypes
{   
    GM_Base,
    GM_Bullet,
    GM_Entity
};

#include "../object/object.h"
class GameObject : public Object
{
private:
    int    _gmType        = GM_Base;
    bool   _isPhysical    = 0;
    bool   _isCollide     = 0;
    bool   _isStay        = 0;
    double _accelerationH = 0;
    double _accelerationV = 0;
    double _mass          = 1;
    double _impact        = 1;
    int _angle         = 0;
public:

    GameObject();
    GameObject(Framework   &fw,
               SDL_Texture* texture,
               SDL_Rect     hitbox,
               int          type       = GM_Base,
               double       mass       = 1,
               double       impact     = 1,
               int       angle      = 0,
               bool         isPhysical = 0,
               bool         isCollide  = 0);

    int    getGMType();
    bool   getIsPhysical();
    bool   getIsCollide();
    bool   getIsStay();
    double getAccelerationH();
    double getAccelerationV();
    double getMass();
    double getImpact();
    int    getAngle();

    void setGMType        (int type);
    void setIsPhysical    (bool isPhysical);
    void setIsCollide     (bool isCollide);
    void setIsStay        (bool isStay);
    void setAccelerationH (double acceleration);
    void setAccelerationV (double acceleration);
    void setMass          (double mass);
    void setImpact        (double impact);
    void setAngle         (int    angle);

    void showViewLine(Framework &fw);
    void render(Framework &fw);
};

#endif
