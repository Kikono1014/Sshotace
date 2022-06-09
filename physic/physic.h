#ifndef PHYSIC_H
#define PHYSIC_H

class Physic
{
private:
    double _gravity;
public:

    Physic(double gravity);

    double getGravity();

    void setGravity(double gravity);

    bool isStayOn(GameObject *object1, GameObject *object2);

    void changeObjСollideAcceleration(GameObject *object1, GameObject *object2);

    void changeObjPositionHorizontal(GameObject *object, Framework &fw, double frictional, int camType);
    void changeObjPositionVertical  (GameObject *object, Framework &fw, double frictional, int camType);
    void changeObjPosition          (GameObject *object, Framework &fw, double frictional, int camType);
    void changeObjPosition          (GameObject *object, Framework &fw);

    int getDirection(double value);
    int getAngle    (double x, double y);

    void moveObj(GameObject *object, double x, double y, double moveForce);
    void moveObj(GameObject *object, int angle, double moveForce);
    void jumpObj(GameObject *object, double jumpForce);
    void flyObj (GameObject *object, double jumpForce);
};

#endif
