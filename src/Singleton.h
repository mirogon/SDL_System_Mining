#pragma once


#include <string>
#include <sstream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <android/log.h>
//#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "randomNumber.h"

#define _FontPath "opensans.ttf"
#define _GrassTexturePath "grass.png"
#define _CoalTexturePath "coal.png"
#define _IronTexturePath "iron.png"

namespace m1{
    
    bool IsInCollisionBox(int x, int y, const SDL_Rect& collisionBox);
    
    inline bool IsInCollisionBox(int x, int y, const SDL_Rect& collisionBox){
        
        if(x < ( collisionBox.x + collisionBox.w ) && ( x > collisionBox.x ) ){
            
            if( y < ( collisionBox.y + collisionBox.h ) && ( y > collisionBox.y ) ){
                
                return true;
                
            }
            
            
        }
        
        return false;
        
    }
    
    template <typename T>
    std::string to_string(T value)
    {
        std::ostringstream os ;
        os << value ;
        return os.str() ;
        
    }
    
    long stol(std::string str);
    
    inline long stol(std::string str)
    {
        std::stringstream sstr(str);
        long rt;
        sstr >> rt;
        return rt;
    }
    
    void androidLog(const char* cstr, int delay = 0);
    
    inline void androidLog(const char* cstr, int delay){
        
       
        if(delay>0){
            SDL_Delay(delay);
        }
        
        __android_log_print(ANDROID_LOG_FATAL, "TRACKER_M1", "%s", cstr );
    
        
    }
    
    void SDL_WriteChar(SDL_RWops* rops, const char* c);
    
    inline void SDL_WriteChar(SDL_RWops* rops, const char* c){
        
        SDL_RWwrite(rops, c, 1, SDL_strlen(c));
        
    }
}


template <typename T>
class C_Singleton{

public:

static T* GetSingleton(){

    if(Singleton==nullptr){

        Singleton = new T();

    }

    return Singleton;

}

void DeleteSingleton(){

    delete Singleton;
    Singleton = nullptr;

}



private:

static T* Singleton;

protected:

C_Singleton(){}

};


template <typename T> T* C_Singleton<T>::Singleton = nullptr;
