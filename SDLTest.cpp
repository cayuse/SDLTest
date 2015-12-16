#include <iostream>
#include <string>
#include <SDL.h>
#include "res_path.h"
#include "cleanup.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 40;


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
	if (texture == nullptr){
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}

/**
* Loads a BMP image into a texture on the rendering device
* @param file The BMP image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	//Initialize to nullptr to avoid dangling pointer issues
	SDL_Texture *texture = nullptr;
	//Load the image
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//If the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Make sure converting went ok too
		if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}*/

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

if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
	logSDLError(std::cout, "SDL_Init");
	return 1;
}

if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
	logSDLError(std::cout, "IMG_Init");
	SDL_Quit();
	return 1;
}

SDL_Window *window = SDL_CreateWindow("Lesson 2", 100, 100, SCREEN_WIDTH,
	SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
if (window == nullptr){
	logSDLError(std::cout, "CreateWindow");
	SDL_Quit();
	return 1;
}
SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
if (renderer == nullptr){
	logSDLError(std::cout, "CreateRenderer");
	cleanup(window);
	SDL_Quit();
	return 1;
}

/*
const std::string resPath = getResourcePath("Lesson2");
SDL_Texture *background = loadTexture(resPath + "background.bmp", renderer);
SDL_Texture *image = loadTexture(resPath + "image.bmp", renderer);
if (background == nullptr || image == nullptr){
	cleanup(background, image, renderer, window);
	SDL_Quit();
	return 1;
}
*/

const std::string resPath = getResourcePath("Lesson3");
SDL_Texture *background = loadTexture(resPath + "background.png", renderer);
SDL_Texture *image = loadTexture(resPath + "image.png", renderer);
//Make sure they both loaded ok
if (background == nullptr || image == nullptr){
	cleanup(background, image, renderer, window);
	IMG_Quit();
	SDL_Quit();
	return 1;
}

SDL_RenderClear(renderer);

int bW, bH;
SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
renderTexture(background, renderer, 0, 0);
renderTexture(background, renderer, bW, 0);
renderTexture(background, renderer, 0, bH);
renderTexture(background, renderer, bW, bH);

int iW, iH;
SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
int x = SCREEN_WIDTH / 2 - iW / 2;
int y = SCREEN_HEIGHT / 2 - iH / 2;
renderTexture(image, renderer, x, y);

SDL_RenderPresent(renderer);
SDL_Delay(1000);

//Determine how many tiles we'll need to fill the screen
int xTiles = SCREEN_WIDTH / TILE_SIZE;
int yTiles = SCREEN_HEIGHT / TILE_SIZE;

//Draw the tiles by calculating their positions
for (int i = 0; i < xTiles * yTiles; ++i){
	int x = i % xTiles;
	int y = i / xTiles;
	renderTexture(background, renderer, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE,
		TILE_SIZE);
}

 iW, iH;
SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
 x = SCREEN_WIDTH / 2 - iW / 2;
 y = SCREEN_HEIGHT / 2 - iH / 2;
renderTexture(image, renderer, x, y);



SDL_RenderPresent(renderer);
SDL_Delay(2000);

cleanup(background, image, renderer, window);
SDL_Quit();

}
