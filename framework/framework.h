#ifndef FRAMEWORK_H
#define FRAMEWORK_H

using std::vector;
using std::map;

class Framework
{
private:
    int           _width;              // Width of the window
    int           _height;             // Height of the window
    double        _renderDelay;
    Uint8         _r;
    Uint8         _g;
    Uint8         _b;
    Uint8         _a;
    SDL_Window   *_window   {nullptr}; // Pointer for the window
    SDL_Renderer *_renderer {nullptr}; // Pointer for the renderer

    vector<SDL_Texture*> _textures;
    vector<Mix_Chunk*>   _samples;
    map<char*, Timer*>   _timers;
public:

    Framework(int width = 500, int height = 500,
              char* title = (char*)"None Titled",
              double delay = 1000/60,
              Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 1);
    
    Framework(vector<char*> texturePath,
              vector<char*> samplePaths,
              int width = 500, int height = 500,
              char* title = (char*)"None Titled",
              double delay = 1000/60,
              Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 1);

    int           getWidth();
    int           getHeight();
    double        getRenderDelay();
    SDL_Window*   getWindow();
    SDL_Renderer* getRenderer();
    SDL_Texture*  getTexture(int id);
    Mix_Chunk*    getSample(int id);

    void setWidth      (int width);
    void setHeight     (int height);
    void setRenderDelay(double delay);

    void updateScreen();
    void updateTimers();
    void playSample  (int id);

    SDL_Texture* importTexture (char* texturePath);
    void addTexture            (char* texturePath);
    void addTexture            (vector<char*> texturePaths);
    void addTexture            (char** texturePaths, int size);

    Mix_Chunk* importSample    (char* samplePath);
    void addSample             (char* samplePath);
    void addSample             (vector<char*> samplePaths);
    void addSample             (char** samplePaths, int size);

    void   newTimer    (char* id, int end);
    void   deleteTimer (char* id);
    void   resetTimer  (char* id);
    bool   checkTimer  (char* id);
    bool   isExistTimer(char* id);
    Timer* getTimer    (char* id );

    ~Framework();
};
#endif
