#include "../config.h"
#include "../timer/timer.h"
#include "../framework/framework.h"
#include "../object/object.h"
#include "./gameObject.h"

GameObject::GameObject() :
Object()
{
}

GameObject::GameObject(Framework   &fw,
                       SDL_Texture* texture,
                       SDL_Rect     hitbox,
                       int          type,
                       double       mass,
                       double       impact,
                       int       angle,
                       bool         isPhysical,
                       bool         isCollide) :
Object(fw, texture, hitbox)
{
    _gmType     = type;
    _isPhysical = isPhysical; 
    _isCollide  = isCollide;
    _mass       = mass;
    _impact     = impact;
    _angle      = angle;
}

int    GameObject::getGMType()        { return _gmType;        }
bool   GameObject::getIsPhysical()    { return _isPhysical;    }
bool   GameObject::getIsCollide()     { return _isCollide;     }
bool   GameObject::getIsStay()        { return _isStay;        }
double GameObject::getAccelerationH() { return _accelerationH; }
double GameObject::getAccelerationV() { return _accelerationV; }
double GameObject::getMass()          { return _mass;          }
double GameObject::getImpact()        { return _impact;        }
int    GameObject::getAngle()         { return _angle;         }

void GameObject::setGMType        (int    type        ) { _gmType              = type;         }
void GameObject::setIsPhysical    (bool   isPhysical  ) { _isPhysical          = isPhysical;   }
void GameObject::setIsCollide     (bool   isCollide   ) { _isCollide           = isCollide;    }
void GameObject::setIsStay        (bool   isStay      ) { _isStay              = isStay;       }
void GameObject::setAccelerationH (double acceleration) { _accelerationH       = acceleration; }
void GameObject::setAccelerationV (double acceleration) { _accelerationV       = acceleration; }
void GameObject::setMass          (double mass        ) { _mass                = mass;         }
void GameObject::setImpact        (double impact      ) { _impact              = impact;       }
void GameObject::setAngle         (int    angle       ) { _angle               = angle;        }

void GameObject::showViewLine(Framework &fw)
{
    double centerX = getX() + getWidth() / 2;
    double centerY = getY() + getHeight() / 2;
    double viewX = centerX + sin(_angle * M_PI / 180) * getWidth();
    double viewY = centerY - cos(_angle * M_PI / 180) * getHeight();

    SDL_RenderDrawLine(fw.getRenderer(), centerX, centerY, viewX, viewY);
}

void GameObject::render(Framework &fw)
{
    SDL_Rect hitboxT {
        getX(), getY(), 
        getWidth(), getHeight()
    };
    SDL_RenderCopyEx(fw.getRenderer(), getTexture(), nullptr, &hitboxT, _angle, nullptr, SDL_FLIP_NONE);
}