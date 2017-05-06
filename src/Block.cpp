#include "Block.h"

C_Block::C_Block()
{
    
    //m1::androidLog("Before grassTexture init", 1);
    
    if(grassTexture == nullptr)
    {   
       // m1::androidLog("grassTexture 1", 1);
        grassTexture = new C_Texture;
        
      //  m1::androidLog("grassTexture 2", 1);
        grassTexture->InitTexture(_GrassTexturePath);

       // m1::androidLog("grassTexture 3", 1); 
        blockRectDouble.w = grassTexture->GetRect()->w;
        
      //  m1::androidLog("grassTexture 4", 1);
        blockRectDouble.h = grassTexture->GetRect()->h;
        
      //  m1::androidLog("grassTexture 5", 1);
        
        
        if(grassTexture == nullptr)
        {
            m1::androidLog("grassTexture could not be created!");
        }
    }
    
   // m1::androidLog("After grassTexture init", 1);
    
    if(coalTexture == nullptr)
    { 
        coalTexture = new C_Texture; 
        coalTexture->InitTexture(_CoalTexturePath); 
        blockRectDouble.w = coalTexture->GetRect()->w;
        blockRectDouble.h = coalTexture->GetRect()->h;
        if(!coalTexture)
        {
            m1::androidLog("coalTexture could not be created!");
        }
    }    
    
            //    SDL_Delay(1);
           // m1::androidLog("bl3");
    
    if(ironTexture == nullptr)
    { 
        ironTexture = new C_Texture;
        ironTexture->InitTexture(_IronTexturePath); 
        blockRectDouble.w = ironTexture->GetRect()->w;
        blockRectDouble.h = ironTexture->GetRect()->h;
        
        if(!ironTexture)
        {
            m1::androidLog("ironTexture could not be created!");
        }
    }
            //    SDL_Delay(1);
           // m1::androidLog("bl4");
}

C_Block::~C_Block(){
    
}



void C_Block::DeleteStaticMember()
{
    delete grassTexture;
    delete coalTexture;
    delete ironTexture;
    
    grassTexture = nullptr;
    coalTexture = nullptr;
    ironTexture = nullptr;
}
void C_Block::ChangeBlockType(e_BlockType newType)
{
    this->blockType = newType;
}

C_Texture* C_Block::grassTexture = nullptr;
C_Texture* C_Block::coalTexture = nullptr;
C_Texture* C_Block::ironTexture = nullptr;
