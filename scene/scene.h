#ifndef SCENE_H
#define SCENE_H
#include <vector>

using std::vector;

class Scene
{
private:
    int _width;
    int _height;
    /**
     * types:
     * 0 = sideways cam;
     * 1 = top cam;
    **/
    int _type = 0;
    char* _name = (char*)"Noname";
    vector<GameObject*> objects;
    SDL_Texture *texture {nullptr};
public:
    Scene(Framework &fw, int width, int height, char* name, int type);
    Scene(Framework &fw, int width, int height, char* name, int type, SDL_Texture* background);

    int getType();

    void setType(int type);

    void add         (GameObject *object);
    void add         (GameObject  object);
    void disintegrate(int id);

    void processingObjGetOut (Framework &fw, Physic &physic);
    void processingObjCollide(Framework &fw, Physic &physic, GameObject *object);
    void processingObj       (Framework &fw, Physic &physic, Scene &scene, double friction);
    void render              (Framework &fw);
    void renderHitbox        (Framework &fw);
};
#endif
