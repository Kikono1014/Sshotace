#include <cmath>
#include "../config.h"
#include "../timer/timer.h"
#include "../framework/framework.h"
#include "../gameObject/gameObject.h"
#include "./physic.h"

Physic::Physic(double gravity)
{
    _gravity = gravity;
}

double Physic::getGravity() { return _gravity; }

void Physic::setGravity(double gravity) { _gravity = gravity; }

bool Physic::isStayOn(GameObject *object1, GameObject *object2)
{
    return (object1->getY() + object1->getHeight() <= object2->getY() - 3) &&
           (object1->getY() + object1->getHeight() >= object2->getY());
}


void Physic::changeObjСollideAcceleration(GameObject *object1, GameObject *object2)
{
    if (object2->isTouchHitboxUp(object1)) {
        object1->setY(object2->getY() - object1->getHeight());
    }
    else if (object2->isTouchHitboxBottom(object1)) {
        object1->setY(object2->getY() + object2->getHeight());
    }
    if (object2->isTouchHitboxLeft(object1)) {
        object1->setX(object2->getX() - object1->getWidth());
    }
    else if (object2->isTouchHitboxRight(object1)) {
        object1->setX(object2->getX() + object2->getWidth());
    }    

    object1->setAccelerationH(-object1->getAccelerationH() * object2->getImpact());
    object1->setAccelerationV(-object1->getAccelerationV() * object2->getImpact());
}



void Physic::changeObjPositionHorizontal(GameObject *object, Framework &fw, double frictional, int camType)
{
    double frictionalForce = 0;
    switch (camType)
    {
        case 0:
            frictionalForce = (object->getMass() * ((object->getY() + object->getHeight() < fw.getHeight()) ? 0.05 : frictional));
            break;
        case 1:
            frictionalForce = (object->getMass() * frictional);
            break;
    }

    if (!object->getIsStay()) {
        if (object->getAccelerationH() == abs(object->getAccelerationH())) {
            object->setAccelerationH((object->getAccelerationH() - frictionalForce));
        }
        if (object->getAccelerationH() != abs(object->getAccelerationH())) {
            object->setAccelerationH((object->getAccelerationH() + frictionalForce));
        }
    }

    // if (abs(object->getAccelerationH()) < 0.1) {
    //     object->setAccelerationH(0);
    // }
}

void Physic::changeObjPositionVertical(GameObject *object, Framework &fw, double frictional, int camType)
{    
    switch (camType)
    {
        case 0:
            {
                if ((object->getY() < fw.getHeight()) && (object->getY() + object->getHeight() > fw.getHeight())) {
                    object->setY(fw.getHeight() - object->getHeight());
                    object->setAccelerationV(-object->getAccelerationV() * object->getImpact());
                }
                if (!object->getIsStay()) {
                    object->setAccelerationV(object->getAccelerationV() - (object->getMass() * _gravity));
                }
                bool condition = (object->getY() > fw.getHeight())
                            || ((object->getY() + object->getHeight() - 5 < fw.getHeight())
                            &&  (object->getY() + object->getHeight() > fw.getHeight()));
                if (condition) {
                    object->setY(fw.getHeight() - object->getHeight());
                    object->setAccelerationV(0);
                    object->setIsStay(1);
                }
                if (!object->getIsStay()) {
                    object->setY(object->getY() - object->getAccelerationV());
                }
            }
            break;
        case 1:
            double frictionalForce = (object->getMass() * frictional);
            if (!object->getIsStay()) {
                if (object->getAccelerationV() > 0) {
                    object->setAccelerationV((object->getAccelerationV() - frictionalForce));
                }
                if (object->getAccelerationV() < 0) {
                    object->setAccelerationV((object->getAccelerationV() + frictionalForce));
                }
            }
            break;
    }
}

void Physic::changeObjPosition(GameObject *object, Framework &fw, double frictional, int camType)
{
    int x = object->getX();
    int y = object->getY();
    changeObjPositionHorizontal(object, fw, frictional, camType);
    changeObjPositionVertical(object, fw, frictional, camType);

    object->setX(x + object->getAccelerationH());  
    object->setY(y - object->getAccelerationV());

    std::cout << object->getAngle() << "\t" << object->getAccelerationH() << "\t" 
                << x << "\t" << round(x + object->getAccelerationH()) << std::endl;

    std::cout << object->getAngle() << "\t" << object->getAccelerationV() << "\t" 
                << y << "\t" << round(y - object->getAccelerationV()) << std::endl;

    if (camType == 0) {
        bool condition = (object->getAccelerationH() == 0) && (object->getAccelerationV() == 0);
        if (condition) {
            object->setIsStay(1);
        }
    }
    if (camType == 1) {
        bool condition = ((x == object->getX()) && (y == object->getY()))
                       || (object->getGMType() == GM_Bullet && ((x == 0) || (x + object->getWidth() == fw.getWidth())
                       || (y == 0) || (y + object->getHeight() == fw.getHeight())));
        if (condition) {
            object->setIsStay(1);
        }
    }
}


void Physic::changeObjPosition(GameObject *object, Framework &fw)
{
    object->setX(object->getX() + object->getAccelerationH());
    object->setY(object->getY() - object->getAccelerationV());
}

int Physic::getDirection(double value)
{
    if (value) {
        return value / abs(value);
    }
    return 0;
}

int Physic::getAngle(double x, double y)
{
    int dx = getDirection(x);
    int dy = getDirection(y);
    int angle = 0;

    if (dy < 0 && dx >= 0) {
        angle = atan(abs(x) / abs(y)) * 180 / M_PI;
    }
    if (dy >= 0 && dx > 0) {
        angle = 90 + atan(abs(y) / abs(x)) * 180 / M_PI;
    }
    if (dy > 0 && dx <= 0) {
        angle = 180 + atan(abs(x) / abs(y)) * 180 / M_PI;
    }
    if (dy <= 0 && dx < 0) {
        angle = 270 + atan(abs(y) / abs(x)) * 180 / M_PI;
    }
    return angle;
}

void Physic::moveObj(GameObject *object, double x, double y, double moveForce)
{
    int dx = getDirection(x);
    int dy = getDirection(y);
    int angle = getAngle(x, y);

    moveObj(object, angle, moveForce);

    object->setIsStay(0);
}

void Physic::moveObj(GameObject *object, int angle, double moveForce)
{
    object->setX(object->getX() + sin(angle * M_PI / 180) * moveForce);
    if (object->getIsPhysical()) {
        object->setAccelerationH(abs(sin(angle * M_PI / 180) * moveForce));
    }

    object->setY(object->getY() - cos(angle * M_PI / 180) * moveForce);
    if (object->getIsPhysical()) {
        object->setAccelerationV(abs(cos(angle * M_PI / 180) * moveForce));
    }
    
    object->setIsStay(0);
}

void Physic::jumpObj(GameObject *object, double jumpForce)
{
    flyObj(object, jumpForce);        
}

void Physic::flyObj(GameObject *object, double jumpForce)
{
    object->setY(object->getY() - (jumpForce - _gravity * object->getMass()));
    if (object->getIsPhysical()) {
        object->setAccelerationV((jumpForce - (object->getMass() * _gravity)) / object->getMass());
    }
    object->setIsStay(0);
}

