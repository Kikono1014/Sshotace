#include "../config.h"
#include "../timer/timer.h"
#include "../framework/framework.h"
#include "../gameObject/gameObject.h"
#include "../bullet/bullet.h"
#include "../physic/physic.h"
#include "./scene.h"
#include "../entity/entity.h"
#include "../mob/mob.h"

Scene::Scene(Framework &fw, int width, int height, char* name, int type)
{
    _width = width;
    _height = height;
    _name = name;
    _type = type;
}

Scene::Scene(Framework &fw, int width, int height, char* name, int type, SDL_Texture* background)
{
    _width = width;
    _height = height;
    _name = name;
    _type = type;
    texture = background;
}


int Scene::getType() { return _type; }

void Scene::setType(int type) { _type = type; }

void Scene::add(GameObject *object)
{
    objects.push_back(object);
}

void Scene::disintegrate(int id)
{
    if (objects[id] != nullptr) {
        delete objects[id];
        objects.erase(objects.begin() + id);
    }
}


void Scene::processingObjGetOut(Framework &fw, Physic &physic)
{
    for (int i = 0; i < objects.size(); ++i) {
        if (objects[i]->getX() < 0) {
            objects[i]->setX(0);
            if (objects[i]->getIsPhysical()) {
                objects[i]->setAccelerationH(-objects[i]->getAccelerationH() * objects[i]->getImpact());
            }
        }
        if (objects[i]->getX() + objects[i]->getWidth() >= fw.getWidth()){
            objects[i]->setX(fw.getWidth() - objects[i]->getWidth());
            if (objects[i]->getIsPhysical()) {
                objects[i]->setAccelerationH(-objects[i]->getAccelerationH() * objects[i]->getImpact());
            }
        }
        if (objects[i]->getY() < 0) {
            objects[i]->setY(0);
            if (objects[i]->getIsPhysical()) {
                objects[i]->setAccelerationV(-objects[i]->getAccelerationV() * objects[i]->getImpact());
            }
        }
        if (objects[i]->getY() + objects[i]->getHeight() >= fw.getHeight()){
            objects[i]->setY(fw.getHeight() - objects[i]->getHeight());
            if (objects[i]->getIsPhysical()) {
                objects[i]->setAccelerationV(-objects[i]->getAccelerationV() * objects[i]->getImpact());
            }
        }

        bool condition = (objects[i]->getX() < 0) || (objects[i]->getX() + objects[i]->getWidth() >= fw.getWidth())
                      || (objects[i]->getY() < 0) || (objects[i]->getY() + objects[i]->getHeight() >= fw.getHeight());
        if (objects[i]->getGMType() == GM_Bullet && condition) {
            disintegrate(i);
        }
    }
}

void Scene::processingObjCollide(Framework &fw, Physic &physic, GameObject *object)
{
    for (int i = 0; i < objects.size(); ++i) {
        if (object->isTouchHitbox(objects[i])) {
            if (objects[i]->getIsPhysical()) {
                physic.changeObjСollideAcceleration(objects[i], object);
            }
            if (objects[i]->getGMType() == GM_Bullet && object->getGMType() == GM_Entity) {
                ((Entity*)object)->hit(((Bullet*)objects[i])->getDamage());
                disintegrate(i);
                break;
            }
        }
    }
}


void Scene::processingObj(Framework &fw, Physic &physic, Scene &scene, double friction)
{
    for (int i = 0; i < objects.size(); ++i) {
        processingObjGetOut(fw, physic);

        if (objects[i]->getIsPhysical()) {
            physic.changeObjPosition(objects[i], fw, friction, _type);
        }
        if (!objects[i]->getIsPhysical()) {
            physic.changeObjPosition(objects[i], fw);
        }

        if (objects[i]->getIsCollide()) {
            processingObjCollide(fw, physic, objects[i]);
        }

        if (objects[i]->getGMType() == GM_Entity) {
            if (((Entity*)objects[i])->getENType() == EN_Mob) {
                Mob *mob = (Mob*)objects[i];
                mob->doScript(fw, scene, physic, mob);
            }

            if (((Entity*)objects[i])->getHealthPoints() <= 0) {
                disintegrate(i);
                break;
            }
        }

        if (objects[i]->getGMType() == GM_Bullet) {
            bool condition = (objects[i]->getAccelerationH() == 0 && objects[i]->getAccelerationV() == 0) || objects[i]->getIsStay();
            if (condition) {
                disintegrate(i);
                break;
            }
        }
    }
}

void Scene::render(Framework &fw)
{
    SDL_Rect r{0, 0, _width, _height};
    SDL_RenderCopy(fw.getRenderer(), texture, nullptr, &r);
    for (int i = 0; i < objects.size(); ++i) {
        objects[i]->render(fw);
    }
}

void Scene::renderHitbox(Framework &fw)
{
    for (int i = 0; i < objects.size(); ++i) {
        SDL_SetRenderDrawColor(fw.getRenderer(), 255, 255, 10, 0);
        objects[i]->showHitbox(fw);
        SDL_SetRenderDrawColor(fw.getRenderer(), 10, 255, 255, 0);
        objects[i]->showViewLine(fw);
    }
}