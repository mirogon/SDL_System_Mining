#pragma once
#include "Block.h"

e_BlockType CharToBlockType(char c);

struct S_ResourceChunk{
    
    char chunkType;
    short lowRange;
    short highRange;
    
};

//CHUNK PROPERTIES
const float resourceChunkChance = 10;
const float resourceChunkResourceChance = 90;
const int chunkSizeX = 8;
const int chunkSizeY = 8;

//CHUNK POSSIBILLITIES ( SHOULD ADD TO 100 ) 
const float coalChunkChance = 50.0f;
const float ironChunkChance = 50.0f;

class C_Map : C_Random{
    
public:
    
    C_Map();
    ~C_Map();
    
    void GenerateMap(int sizeX = 512, int sizeY = 512);
    void SaveMap(int slot = 1);
    void LoadMap(int loadSlot = 1);
    
    void RenderMap();
    
private:
    
    int mapSizeX;
    int mapSizeY;
    std::vector<S_ResourceChunk> resourceChunks;
    std::vector<C_Block> map;
    
};

inline void C_Map::RenderMap(){
    
    for(std::vector<C_Block>::iterator i = map.begin(); i != map.end(); ++i){
        
        i->RenderBlock();
        
    }
    
}