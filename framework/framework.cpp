#include "../config.h"
#include "../timer/timer.h"
#include "./framework.h"

Framework::Framework(int width, int height,
                     char* title,
                     double delay,
                     Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    _width        = width;
    _height       = height;
    _renderDelay  = delay;

    _r = r;
    _g = g;
    _b = b;
    _a = a;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {       // Initializing SDL as Video
        printf("(ERR) SDL could not initialize! SDL_Error %s\n", SDL_GetError());
    }
    else {
        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
        TTF_Init();

        if ( Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512) < 0 ) {
            printf("(ERR) Unable to open audio: %s\n", SDL_GetError());
        }

        if ( Mix_AllocateChannels(4) < 0 ) {
            printf("(ERR) Unable to allocate mixing channels: %s\n", SDL_GetError());
        }

        _window = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED_MASK,
                                  SDL_WINDOWPOS_CENTERED_MASK,
                                  width,
                                  height,
                                  SDL_WINDOW_RESIZABLE);
        if (_window == nullptr) {
            printf("(ERR) Window could not be created! SDL_Error %s\n", SDL_GetError());
        }
        else {
            _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC);
            SDL_SetRenderDrawColor(_renderer, r, g, b, a);
            SDL_RenderClear(_renderer);
            SDL_RenderPresent(_renderer);
        }
    }

    newTimer((char*)"RenderTimer", _renderDelay);
}


Framework::Framework(vector<char*> texturePath,
                     vector<char*> samplePaths,
                     int width, int height,
                     char* title,
                     double delay,
                     Uint8 r, Uint8 g, Uint8 b, Uint8 a) :
Framework(width, height, title, delay, r, g, b, a)
{
    addTexture(texturePath);
    addSample(samplePaths);
}



int           Framework::getWidth      ()       { return _width;        }
int           Framework::getHeight     ()       { return _height;       }
double        Framework::getRenderDelay()       { return _renderDelay;  }
SDL_Window*   Framework::getWindow     ()       { return _window;       }
SDL_Renderer* Framework::getRenderer   ()       { return _renderer;     }
SDL_Texture*  Framework::getTexture    (int id) { return _textures[id]; }
Mix_Chunk*    Framework::getSample     (int id) { return _samples[id];  }

void Framework::setWidth      (int width)     { _width  = width ;     }
void Framework::setHeight     (int height)    { _height = height;     }
void Framework::setRenderDelay(double delay)  { _renderDelay = delay; }

void Framework::updateScreen()
{
    char* timerName = (char*)"RenderTimer";
    if (isExistTimer(timerName)) {
        if (checkTimer(timerName)) {
            SDL_RenderPresent(_renderer);
            SDL_Delay(1);
            SDL_SetRenderDrawColor(_renderer, _r, _g, _b, _a);
            SDL_RenderClear(_renderer);
            resetTimer(timerName);
        }
    }
}

void Framework::updateTimers()
{
    map<char*, Timer*>::iterator itr;
    for (itr = _timers.begin(); itr != _timers.end(); ++itr) {
        _timers[itr->first]->ticks++;
    }
}


void Framework::playSample(int id)
{
    Mix_PlayChannel(-1, _samples[id], 0);
}

SDL_Texture* Framework::importTexture(char* texturePath) {
    SDL_Texture* texture {nullptr};
    SDL_Surface* surface = IMG_Load(texturePath);
    if(!surface) {
        printf("(ERR) Texture %s not found!\n", texturePath);
        surface = IMG_Load("assets/common/error.png");
    }
    texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Framework::addTexture(char* texturePath)
{
    _textures.push_back(importTexture(texturePath));
}

void Framework::addTexture(vector<char*> texturePaths)
{
    for(int i = 0; i < texturePaths.size(); ++i) {
        addTexture(texturePaths[i]);
    }
}

void Framework::addTexture(char** texturePaths, int size)
{
    for(int i = 0; i < size; ++i) {
        addTexture(texturePaths[i]);
    }
}

Mix_Chunk* Framework::importSample(char* samplePath)
{
    return Mix_LoadWAV(samplePath);
}

void Framework::addSample(char* samplePath)
{
    _samples.push_back(importSample(samplePath));
    if( _samples[_samples.size() - 1] == nullptr ) {
        printf("(ERR) Texture %s not found!\n", samplePath);
    }
}

void Framework::addSample(vector<char*> samplePaths)
{
    for(int i = 0; i < samplePaths.size(); ++i) {
        addSample(samplePaths[i]);
    }
}

void Framework::addSample(char** samplePaths, int size)
{
    for(int i = 0; i < size; ++i) {
        addSample(samplePaths[i]);
    }
}



void Framework::newTimer(char* id, int end)
{
    Timer *t = (Timer*)malloc(sizeof(Timer));
    *t = Timer{ 0, end };
    _timers[id] = t;
}


void Framework::deleteTimer(char* id)
{
    if (isExistTimer(id)) {
        delete _timers[id];
        _timers.erase(id);
    }
    else {
        printf("(ERR) Timer: \"%s\" does not exist \n", id);
    }
    
}

void Framework::resetTimer (char* id)
{
    if (isExistTimer(id)) {
        _timers[id]->ticks = 0;
    }
    else {
        printf("(ERR) Timer: \"%s\" does not exist \n", id);
    }
}

bool Framework::checkTimer (char* id)
{
    if (isExistTimer(id)) {
        return _timers[id]->ticks >= _timers[id]->endtime;
    }
    else {
        printf("(ERR) Timer: \"%s\" does not exist \n", id);
        return 0;
    }
    
}

bool Framework::isExistTimer(char* id)
{
    return _timers.find(id) != _timers.end();
}

Timer* Framework::getTimer(char* id)
{
    if (!isExistTimer(id)) {
        printf("(ERR) Timer: \"%s\" does not exist \n", id);
    }
    return _timers[id];
}






// Destructor
Framework::~Framework(){

    for( int i = 0; i < _samples.size(); i++ ) {
        Mix_FreeChunk(_samples[i]);
    }
    for( int i = 0; i < _textures.size(); i++ ) {
        SDL_DestroyTexture(_textures[i]);
    }
    SDL_DestroyWindow(_window);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_CloseAudio();
}
