#pragma once
#include "Texture.h"

struct double_Rect{

    double x;
    double y;
    int w;
    int h;


};

class C_Object : public C_Texture{

public:

bool scoreable;

//METHODS

C_Object();
~C_Object();

void InitObject(std::string path);
void MoveObjectDirect(int x, int y);


//INLINE

const double_Rect* GetObjectRect();
void MoveObject(double x, double y);
void RenderObject();

protected:

double_Rect* textureRectDouble;

}; // CLASS

inline void C_Object::MoveObject(double x, double y){

    textureRectDouble->x += x;
    textureRectDouble->y += y;

}

inline void C_Object::RenderObject(){

    textureRect->x = textureRectDouble->x;
    textureRect->y = textureRectDouble->y;

    SDL_RenderCopy(_GetRenderer, this->texture, NULL, textureRect);


}

inline const double_Rect* C_Object::GetObjectRect(){

    return textureRectDouble;

}

