#include "./config.h"
#include "./timer/timer.h"
#include "./framework/framework.h"
#include "./object/object.h"
#include "./gameObject/gameObject.h"
#include "./physic/physic.h"
#include "./scene/scene.h"
#include "./bullet/bullet.h"
#include "./entity/entity.h"
#include "./player/player.h"
#include "./mob/mob.h"

bool viewHitboxes = 0;

std::vector<int> hadledKeys;

std::vector<char*> texturePaths {
    (char*)"assets/common/error.png",
    (char*)"assets/sprites/player.png",
    (char*)"assets/sprites/bullet.png",
    (char*)"assets/sprites/background.jpg",
    (char*)"assets/sprites/mob.png"
};

std::vector<char*> samplePaths {
    (char*)"assets/sound/Kick-Drum-1.wav",
    (char*)"assets/sound/Snare-Drum-1.wav"
};

Physic physic { 0 };
Framework fw{ texturePaths, samplePaths, 500, 800, (char*)"Engine demo", 10/3 };
Scene scene{ fw, fw.getWidth(), fw.getHeight(), (char*)"Main", 1, fw.getTexture(3) };
SDL_Event event;



void mobScript(Framework &fw, Scene &scene, Physic &physic, Mob *mob)
{
    if (!fw.isExistTimer((char*)"MobShootTimer")) {
        fw.newTimer((char*)"MobShootTimer", 10);
    }
    if (fw.checkTimer((char*)"MobShootTimer")) {
        fw.resetTimer((char*)"MobShootTimer");
    
        Bullet bulletT{ fw, fw.getTexture(2),
                        SDL_Rect { 0,
                                   0,
                                   30, 30
                        },
                        0, 0.5, 0,
                        5,
                        1, 0
        };
        // for (int i = 0; i <= 360; i += 1) {
        //     double x = sin(i * M_PI / 180) * 10;
        //     double y = -cos(i * M_PI / 180) * 10;
        //     mob->shoot(fw, scene, physic, bulletT, x, y, 5);
        // }
        mob->shoot(fw, scene, physic, bulletT, 135, 5, 5);
        mob->shoot(fw, scene, physic, bulletT, 225, 5, 5);
    }
}

Mob mob1{ fw, fw.getTexture(4), SDL_Rect{ 200, 300, 100, 100 }, &mobScript, 200, 2.0, 0, 0, 0, 1 };

Player player{ fw, fw.getTexture(1), SDL_Rect{ 200, 500, 100, 100 }, 20, 0, 100, 1.0, 0, 0, 0, 1 };

void eventProcessing();
void keyProcessing(int key);
void keyDown();
void keyUp();
void buttonProcessing();

int main(int argc, char **argv) {
    Mob *mob1P = new Mob { mob1 };
    // scene.add(mob1P);

    scene.add(&player);

    fw.newTimer((char*)"keyTimer", 12);
    
    while(!(event.type == SDL_QUIT)){
        eventProcessing();
        if (fw.checkTimer((char*)"keyTimer")) {
            fw.resetTimer((char*)"keyTimer");
            for (int i = 0; i < hadledKeys.size(); ++i) {
                keyProcessing(hadledKeys[i]);
            }
        }

        scene.processingObj(fw, physic, scene, 0.15);

        scene.render(fw);
        if (viewHitboxes) {
            scene.renderHitbox(fw);
        }

        fw.updateScreen();
        fw.updateTimers();
    }
}

void eventProcessing()
{
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_WINDOWEVENT:
            switch (event.window.event)  {
            case SDL_WINDOWEVENT_SIZE_CHANGED:  
                int windowWidth = 0;
                int windowHeight = 0;
                SDL_GetWindowSize(fw.getWindow(), &windowWidth, &windowHeight);
                fw.setWidth(windowWidth);
                fw.setHeight(windowHeight);
                break;
            }
        case SDL_KEYUP:
            keyUp();
            break;
        case SDL_KEYDOWN:
            keyDown();
            break;
        case SDL_MOUSEBUTTONDOWN:
            buttonProcessing();
            break;
        case SDL_MOUSEBUTTONUP:
            break;
        }
    }
}


void keyDown()
{
    bool exist = 0;
    for (int i = 0; i < hadledKeys.size(); ++i) {
        exist = (event.key.keysym.sym == hadledKeys[i]);
    }
    if (!exist && (event.key.keysym.sym != 0)) {
        hadledKeys.push_back(event.key.keysym.sym);
    }
}

void keyUp()
{
    for (int i = 0; i < hadledKeys.size(); ++i) {
        if (event.key.keysym.sym == hadledKeys[i]) {
            hadledKeys.erase(hadledKeys.begin() + i);
        }
    }
}

void keyProcessing(int key)
{
    switch (key)
    {
        case SDLK_F3:
            viewHitboxes = !viewHitboxes;
            break;
        case SDLK_d:
            physic.moveObj(&player,  1,  0, player.getMoveForce());
            break;
        case SDLK_a:
            physic.moveObj(&player, -1,  0, player.getMoveForce());
            break;
        case SDLK_w:
            physic.moveObj(&player,  0, -1, player.getMoveForce());
            break;
        case SDLK_s:
            physic.moveObj(&player,  0,  1, player.getMoveForce());
            break;
        case SDLK_LEFT:
            player.setAngle(player.getAngle() - 5);
            break;
        case SDLK_RIGHT:
            player.setAngle(player.getAngle() + 5);
            break;
        case SDLK_SPACE:
            int buttonX = 0;
            int buttonY = 0;
            SDL_GetMouseState(&buttonX, &buttonY);
            int mouseXOfPlayer = buttonX - (player.getX() + (player.getWidth() / 2));
            int mouseYOfPlayer = buttonY - (player.getY() + (player.getHeight() / 2));
            Bullet bulletT{ fw, fw.getTexture(2),
                            SDL_Rect { mouseXOfPlayer,
                                        mouseYOfPlayer,
                                        30, 30
                            },
                            0, 0.5, 0,
                            5,
                            1, 0
            };
            double power = 2;
            double distace = 50;
            player.shoot(fw, scene, physic, bulletT, mouseXOfPlayer, mouseYOfPlayer, power, distace);

            // player.shoot(fw, scene, physic, bulletT, 45  + player.getAngle(), power, distace);
            // player.shoot(fw, scene, physic, bulletT, 135 + player.getAngle(), power, distace);
            // player.shoot(fw, scene, physic, bulletT, 225 + player.getAngle(), power, distace);
            // player.shoot(fw, scene, physic, bulletT, 315 + player.getAngle(), power, distace);
            break;
    }
}

void buttonProcessing() 
{
    switch (event.button.button)
    {
        case SDL_BUTTON_LEFT:
            break;
    }
}
