#include "../config.h"
#include "../timer/timer.h"
#include "../framework/framework.h"
#include "./object.h"

Object::Object()
{
    this->hitbox  = SDL_Rect{0, 0, 0, 0};
}

Object::Object(Framework &fw,
               SDL_Texture* texture,
               SDL_Rect hitbox)
{
    this->hitbox  = hitbox;
    this->texture = texture;
}

SDL_Texture* Object::getTexture() { return texture;  }
SDL_Rect*    Object::getHitbox()  { return(&hitbox); }
int          Object::getWidth()   { return hitbox.w; }
int          Object::getHeight()  { return hitbox.h; }
int          Object::getX()       { return hitbox.x; }
int          Object::getY()       { return hitbox.y; }

void Object::setTextureFromPath(Framework &fw, char* texturePath)
{
    this->texture = fw.importTexture(texturePath);
}

void Object::setTexture(SDL_Texture* texture) { this->texture = texture; }
void Object::setHitbox (SDL_Rect hitbox)      { this->hitbox  = hitbox;  }
void Object::setWidth  (int w)                { hitbox.w      = w;       }
void Object::setHeight (int h)                { hitbox.h      = h;       }
void Object::setX      (int x)                { hitbox.x      = x;       }
void Object::setY      (int y)                { hitbox.y      = y;       }


bool Object::isTouchHitbox(int x, int y) {
    return ((x > hitbox.x) && (x < hitbox.x + hitbox.w)) &&
           ((y > hitbox.y) && (y < hitbox.y + hitbox.h));
}


bool Object::isTouchHitboxUp(Object *object)
{
    return (object->getY() + object->getHeight() > hitbox.x) &&
            (object->getY() + object->getHeight() < hitbox.x + hitbox.w);
}

bool Object::isTouchHitboxBottom(Object *object)
{
    return (object->getY() > hitbox.x) &&
           (object->getY() < hitbox.x + hitbox.w);
}

bool Object::isTouchHitboxLeft(Object *object)
{
    return (object->getX() + object->getWidth() > hitbox.y) &&
           (object->getX() + object->getWidth() < hitbox.y + hitbox.h);
}

bool Object::isTouchHitboxRight(Object *object)
{
    return (object->getX() > hitbox.y) &&
           (object->getX() < hitbox.y + hitbox.h);
}


bool Object::isTouchHitbox(Object *object) {
    return (((object->getX() > hitbox.x) &&
             (object->getX() < hitbox.x + hitbox.w)) ||
            ((object->getX() + object->getWidth() > hitbox.x) &&
             (object->getX() + object->getWidth() < hitbox.x + hitbox.w)))
           &&
           (((object->getY() > hitbox.y) &&
             (object->getY() < hitbox.y + hitbox.h)) ||
            ((object->getY() + object->getHeight() > hitbox.y) &&
             (object->getY() + object->getHeight() < hitbox.y + hitbox.h)));
}


void Object::showHitbox(Framework &fw)
{
    SDL_RenderDrawRect(fw.getRenderer(), &hitbox);
}

void Object::render(Framework &fw)
{
    SDL_RenderCopy(fw.getRenderer(), texture, nullptr, &hitbox);
}
