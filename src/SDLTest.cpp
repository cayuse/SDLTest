#include "Ship.h"
#include <iostream>
#include <string>

#ifdef USING_OSX_FRAMEWORKS
#   include <SDL2/SDL.h>
#   include <SDL2_image/SDL_image.h>
#else
#   include <SDL.h>
#   include <SDL_image.h>
#endif

#include "res_path.h"
#include "cleanup.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
    os << msg << " error: " << SDL_GetError() << std::endl;
}

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
    SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr)
    {
        logSDLError(std::cout, "LoadTexture");
    }
    return texture;
}



/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, with some desired
* width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
* @param w The width of the texture to draw
* @param h The height of the texture to draw
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
    //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(ren, tex, NULL, &dst);
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, with some desired
* width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
* @param w The width of the texture to draw
* @param h The height of the texture to draw
*
* int SDL_RenderCopyEx(SDL_Renderer*          renderer,
                     SDL_Texture*           texture,
                     const SDL_Rect*        srcrect,
                     const SDL_Rect*        dstrect,
                     const double           angle,
                     const SDL_Point*       center,
                     const SDL_RendererFlip flip)
*/
void renderTextureEx(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h, int angle){
    //Setup the destination rectangle to be at the position we want
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopyEx(ren, tex, NULL, &dst, angle, NULL, SDL_FLIP_NONE);
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);
    renderTexture(tex, ren, x, y, w, h);
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
 
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
 //Setup the destination rectangle to be at the position we want
 SDL_Rect dst;
 dst.x = x;
 dst.y = y;
 //Query the texture to get its width and height to use
 SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
 SDL_RenderCopy(ren, tex, NULL, &dst);
}*/


int main(int argc, char **argv){
    Timer delta;
    Ship ship();
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        logSDLError(std::cout, "IMG_Init");
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Space Patrol!", 100, 100, SCREEN_WIDTH,
                                          SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        logSDLError(std::cout, "CreateWindow");
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                             SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        logSDLError(std::cout, "CreateRenderer");
        cleanup(window);
        SDL_Quit();
        return 1;
    }

    const std::string resPath = getResourcePath("ship_art");
    SDL_Texture *image = loadTexture(resPath + "speedship.png", renderer);
    //Make sure they both loaded ok
    if (image == nullptr)
    {
        cleanup(image, renderer, window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_RenderClear(renderer);

    int iW, iH;
    SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;
    renderTextureEx(image, renderer, x, y, 64, 64, 0);

    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    delta.start();
    SDL_Event event;
    int alien_x = x;
    int alien_y = y;
    int alien_angle = 0;
    int alien_xvel = 0;
    int alien_yvel = 0;
    bool quit = false;
    while (!quit)
    {
        while( SDL_PollEvent( &event ) )
        {
            switch( event.type )
            {
                /* Look for a keypress */
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch( event.key.keysym.sym )
                {
                case SDLK_LEFT:
                    alien_xvel = -1;
                    break;
                case SDLK_RIGHT:
                    alien_xvel =  1;
                    break;
                case SDLK_UP:
                    alien_yvel = -1;
                    break;
                case SDLK_DOWN:
                    alien_yvel =  1;
                    break;
                default:
                    break;
                }
                break;
                /* We must also use the SDL_KEYUP events to zero the x */
                /* and y velocity variables. But we must also be       */
                /* careful not to zero the velocities when we shouldn't*/
            case SDL_KEYUP:
                switch( event.key.keysym.sym )
                {
                case SDLK_LEFT:
                    /* We check to make sure the alien is moving */
                    /* to the left. If it is then we zero the    */
                    /* velocity. If the alien is moving to the   */
                    /* right then the right key is still press   */
                    /* so we don't tocuh the velocity            */
                    if( alien_xvel < 0 )
                        alien_xvel = 0;
                    break;
                case SDLK_RIGHT:
                    if( alien_xvel > 0 )
                        alien_xvel = 0;
                    break;
                case SDLK_UP:
                    if( alien_yvel < 0 )
                        alien_yvel = 0;
                    break;
                case SDLK_DOWN:
                    if( alien_yvel > 0 )
                        alien_yvel = 0;
                    break;
                default:
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                quit = true;
                break;
            default:
                break;
            }


        }
        if (alien_xvel > 0)
        {
          ship.rotateCW();
        }
        if (alien_xvel < 0)
        {
          ship.rotateCCW();
        }
        
        if (alien_yvel < 0)
        {
          ship.thrust();
        }
        ship.getPosition(delta.get_ticks(), alien_x, alien_y, alien_angle)
        SDL_RenderClear(renderer);
        renderTextureEx(image, renderer, alien_x, alien_y, 64, 64, alien_angle);
        delta.start();
        SDL_RenderPresent(renderer);
    }
    /* Update the alien position */


    cleanup(image, renderer, window);
    SDL_Quit();

}
