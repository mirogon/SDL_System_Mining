#pragma once

#include "Singleton.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#define _GetWindow ( ( C_Base::GetSingleton() )->GetWindow() )
#define _GetRenderer ( ( C_Base::GetSingleton() )->GetRenderer() )

class C_Base : public C_Singleton<C_Base> {

    friend class C_Singleton<C_Base>;

    public:

    //Methods

    ~C_Base();

    //INLINE

    SDL_Window* GetWindow();

    SDL_Renderer* GetRenderer();

    private:

    SDL_Window* mainWindow;

    SDL_Renderer* mainRenderer;

    protected:

    C_Base();



};


inline SDL_Window* C_Base::GetWindow(){

    return mainWindow;

};

inline SDL_Renderer* C_Base::GetRenderer(){

    return mainRenderer;

};




