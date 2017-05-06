#include "Object.h"


C_Object::C_Object(){

    textureRectDouble = new double_Rect;
    scoreable = true;

}

C_Object::~C_Object(){
    
    ////std::cout<<"object deconstructor"<<std::endl;
    delete textureRectDouble;
    textureRectDouble = nullptr;

}

void C_Object::InitObject(std::string path){

    InitTexture(path);
    textureRectDouble->w = textureRect->w;
    textureRectDouble->h = textureRect->h;

}



void C_Object::MoveObjectDirect(int x, int y){

    textureRectDouble->x = x;
    textureRectDouble->y = y;

}



