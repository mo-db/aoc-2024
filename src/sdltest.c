#include <SDL3/SDL.h>
#include <libavcodec/avcodec.h>

int main()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    AVCodec *codec;
    return 0;
}
