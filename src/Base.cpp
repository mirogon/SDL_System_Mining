#include "Base.h"

C_Base::C_Base():

    //Intializing the mainWindow
    mainWindow{ SDL_CreateWindow("System Mining Dev. Version", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) },

    //Intializing the mainRenderer
    mainRenderer{SDL_CreateRenderer(mainWindow, -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)}


{

    if(!mainWindow){

        //std::cout<<"mainWindow could not be intialized"<<std::endl;
        m1::androidLog("mainWindow could not be created!");
    }

    if(!mainRenderer){

        //std::cout<<"mainRenderer could not be intialized"<<std::endl;
        m1::androidLog("mainRenderer could not be created!");
    }


    //Set the default renderer color
    SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

};

C_Base::~C_Base(){

    //Destroy the mainWindow
    SDL_DestroyWindow(this->mainWindow);

    //Destroy the mainRenderer
    SDL_DestroyRenderer(this->mainRenderer);

};
