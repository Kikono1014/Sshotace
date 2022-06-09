#ifndef OBJ_H
#define OBJ_H

class Object
{
private:
    SDL_Texture *texture {nullptr};
    SDL_Rect hitbox;
public:

    Object();
    Object(Framework &fw,
           SDL_Texture* texture,
           SDL_Rect hitbox);

    SDL_Texture* getTexture();
    SDL_Rect*    getHitbox();
    int          getWidth();
    int          getHeight();
    int          getX();
    int          getY();

    void setTexture        (SDL_Texture* texture);
    void setTextureFromPath(Framework &fw, char* texturePath);
    void setHitbox         (SDL_Rect hitbox);
    void setWidth          (int w);
    void setHeight         (int h);
    void setX              (int x);
    void setY              (int y);


    bool isTouchHitboxUp    (Object *object);
    bool isTouchHitboxBottom(Object *object);
    bool isTouchHitboxLeft  (Object *object);
    bool isTouchHitboxRight (Object *object);

    bool isTouchHitbox(int x, int y);
    bool isTouchHitbox(Object *object);
    
    void showHitbox(Framework &fw);

    void render(Framework &fw);

};

#endif
