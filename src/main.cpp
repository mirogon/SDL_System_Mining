#include "Game.h"

using namespace std;

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

float SCALE_W;
float SCALE_H;

int main(int argc, char* argv[]){
    
    //Create SDL, IMG and TTF
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    //Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
    SDL_DisplayMode dM;
    SDL_GetCurrentDisplayMode(0, &dM);
    
    if(dM.h > dM.w)
    {
        SCREEN_WIDTH = dM.h;
        SCREEN_HEIGHT = dM.w;
        
    }
    
    else if (dM.w > dM.h)
    {
        
        SCREEN_WIDTH = dM.w;
        SCREEN_HEIGHT = dM.h;
        
    }
    
    else
    {
        SCREEN_WIDTH = dM.w;
        SCREEN_HEIGHT = dM.h;
    }
    
    std::string s = "SCREEN WIDTH" + m1::to_string(SCREEN_WIDTH);
    std::string s2 = "SCREEN HEIGHT" + m1::to_string(SCREEN_HEIGHT);
    m1::androidLog(s.c_str());
    m1::androidLog(s2.c_str());
    
    SCALE_W = (float)SCREEN_WIDTH/1280;
    SCALE_H = (float)SCREEN_HEIGHT/720;
    
    m1::androidLog("SCALE_W = ");
    m1::androidLog(m1::to_string(SCALE_W).c_str());
    m1::androidLog("SCALE_H = ");
    m1::androidLog(m1::to_string(SCALE_H).c_str());

    //Start values for the bools
    bool quitPollEvent = false;

    //Event to check the current event
    SDL_Event e;
    
   // 
   
    C_Map mainMap;
    
    mainMap.GenerateMap();

        
    while(quitPollEvent == false){

       // static double loop = 0;

        //Sync the current event
        while( SDL_PollEvent(&e)!= 0 ){

            //Check if the application was closed
            if(e.type == SDL_QUIT){

                //End the application loop
                quitPollEvent = true;
                
                
            }

        }

        //Clears the renderer with the intialized default renderer color
        SDL_RenderClear(_GetRenderer);
        
        //mainMap.RenderMap();

        mainMap.RenderMap();
        //m1::androidLog("Map Rendered");
        
        //Sync the renderer
        SDL_RenderPresent(_GetRenderer);

    }

    //CLEAN THE MEMORY
    C_Block::DeleteStaticMember();
    C_Base::GetSingleton()->DeleteSingleton();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}


