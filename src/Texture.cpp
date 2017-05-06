#include "Texture.h"

C_Texture::C_Texture(){
    

    //std::cout<<"Texture"<<tN<<" wird erstellt"<<std::endl;
    textureRect = new SDL_Rect;
    textureRect->x = 0;
    textureRect->y = 0;
    textureRect->w = 0;
    textureRect->h = 0;

    texture = nullptr;

}

C_Texture::~C_Texture(){
    

    SDL_DestroyTexture(this->texture);
    
    //std::cout<<"Texture "<<tN2<<" wird gelöscht"<<std::endl;
    
    delete textureRect;
    textureRect = nullptr;

}

void C_Texture::FreeTexture(){

    if (texture != nullptr){

        SDL_DestroyTexture(texture);

    }

}

bool C_Texture::InitTexture(std::string path, float scale_w, float scale_h){
    
    FreeTexture();
    
    SDL_Surface* surface = IMG_Load(path.c_str());
    
    if(surface==nullptr){
        
        m1::androidLog("Surface konnte nicht geladen werden (Texture.cpp 46) ");
        //std::cout<<"Surface konnte nicht geladen werden: "<<std::endl<<SDL_GetError();

    }
    
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 255) );

    texture = SDL_CreateTextureFromSurface( _GetRenderer , surface );
    if(texture == nullptr){
        
        m1::androidLog("Textur konnte nicht erstellt werden (Texture.cpp 57)");
        //std::cout<<"Texture konnte nicht Erstellt werden: "<<std::endl<<SDL_GetError();

    }
    textureRect->w = surface->w * scale_w;
    textureRect->h = surface->h * scale_h;

    SDL_FreeSurface(surface);
    return texture != nullptr;

}

/*bool C_Texture::InitTextureFromText(std::string text, float scale, SDL_Color color){

    FreeTexture();

    SDL_Surface* loadText = TTF_RenderText_Solid(_GetFont, text.c_str(), color);
    if(loadText==nullptr){

        //std::cout<<"TTF Surface konnte nicht erstellt werden"<<std::endl;

    }

    SDL_SetColorKey(loadText, SDL_TRUE, SDL_MapRGB(loadText->format, 0, 255, 255));

    texture = SDL_CreateTextureFromSurface(_GetRenderer, loadText);

    textureRect->w = loadText->w * scale;
    textureRect->h = loadText->h * scale;

    SDL_FreeSurface(loadText);

    return texture != nullptr;

}*/
