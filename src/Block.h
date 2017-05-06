#pragma once
#include "Object.h"

enum e_BlockType{ Grass = 0, Coal = 1, Iron = 2 };

class C_Block{
    
public:
    
    C_Block();
    ~C_Block();
    
    void InitBlock(int x, int y, e_BlockType blockType);
    bool RenderBlock() const;
    void MoveBlock(const double& mX, const double& mY);
    
    long GetX() const;
    long GetY() const;
    int GetW() const;
    int GetH() const;
    
    void ChangeBlockType(e_BlockType);
    
    static void DeleteStaticMember();
    
    char* GetBlockType() const{
        
        switch(blockType){
            
            case Grass: return (char*) "0"; break;
            case Coal: return (char*) "1"; break;
            case Iron: return (char*) "2"; break;
            
        }
        
    }
    
private:
    
    e_BlockType blockType;
    
    double_Rect blockRectDouble;
    
    static C_Texture* grassTexture;
    static C_Texture* coalTexture;
    static C_Texture* ironTexture;
};

inline void C_Block::InitBlock(int x, int y, e_BlockType newType)
{
    blockRectDouble.x = x;
    blockRectDouble.y = y;
    
    blockType = newType;
    
}

inline bool C_Block::RenderBlock() const{

    
    switch(blockType){
        
        case Grass: grassTexture->RenderTexture(blockRectDouble.x, blockRectDouble.y); break;
        
        case Coal: coalTexture->RenderTexture(blockRectDouble.x, blockRectDouble.y); break;
        
        case Iron: ironTexture->RenderTexture(blockRectDouble.x, blockRectDouble.y); break;
        
        default: return 1; break;
    }
   
   return 0;

}

inline void C_Block::MoveBlock(const double& mX, const double& mY){
    
    blockRectDouble.x += mX;
    blockRectDouble.y += mY;
    
}


inline long C_Block::GetX() const{

    return blockRectDouble.x;

}

inline long C_Block::GetY() const{

    return blockRectDouble.y;

}

inline int C_Block::GetW() const{
    
    return blockRectDouble.w;
}

inline int C_Block::GetH() const{
    
    return blockRectDouble.h;
}