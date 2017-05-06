#include "Map.h"

e_BlockType CharToBlockType(char c){
    
    switch(c){
        
        case '0': return e_BlockType::Grass; break;
        case '1': return e_BlockType::Coal; break;
        case '2': return e_BlockType::Iron; break;
        default: m1::androidLog("CharToBlockType MISSING CASE TREE! (Map.cpp)"); return e_BlockType::Grass;
    }
    
    
    
}

C_Map::C_Map(){
    
mapSizeX = 100;
mapSizeY = 100;

//ALLOCATE RANGES FOR THE RESOURCE CHUNKS
resourceChunks.push_back(S_ResourceChunk());
resourceChunks[0].chunkType = '1';
resourceChunks[0].lowRange = 0;
resourceChunks[0].highRange = 500;

resourceChunks.push_back(S_ResourceChunk());
resourceChunks[1].chunkType = '2';
resourceChunks[1].lowRange = 500;
resourceChunks[1].highRange = 1000; 
}

C_Map::~C_Map(){
    map.clear();
    resourceChunks.clear();
}

void C_Map::GenerateMap(int sizeX, int sizeY)
{   
    mapSizeX = sizeX;
    mapSizeY = sizeY;
    
    //CLEAR THE MAP IF SOME EXISTS
    map.clear();
    
    //Create 2D Array with the block types later used to intialize the map
    char mapBlockTypes[sizeX][sizeY];
    
    //Set all the values to '0' which represents Grass
    for(int i = 0; i < sizeX; ++i){
        for(int j = 0; j<sizeY;++j){
            mapBlockTypes[i][j]='0';
        }
    }
    
    //CREATE THE NUMBER OF THE CERTAIN RESOURCE CHUNKS
    int chunkNum = (mapSizeX * mapSizeY) / (chunkSizeX * chunkSizeY);
    
    std::string s_CN = "CHUNKS: " + m1::to_string(chunkNum);
    m1::androidLog(s_CN.c_str());
    
    int resourceChunkNum = chunkNum * (resourceChunkChance / 100);
    
    std::string s_RCN = "RESOURCE CHUNKS: " + m1::to_string(resourceChunkNum);
    m1::androidLog(s_RCN.c_str());
    
    char resourceChunkTypes[resourceChunkNum];
    
    for(int i = 0; i < resourceChunkNum;++i){
        
        int rN = randomNumber(1, 1000);
        
        //RANGE ALLOCATION
        for(int j = 0; j < resourceChunks.size(); ++j){
            
            if( rN >= resourceChunks[j].lowRange && ( rN <= resourceChunks[j].highRange ) )
            {
                resourceChunkTypes[i] = resourceChunks[j].chunkType;
            }
        }
        
    }

    //FILL resourceChunkTypes randomly in mapBlockTypes
    for(int i = 0; i < resourceChunkNum; ++i)
    {
        static int chunkStartX = 0;
        static int chunkStartY = 0;
        
        chunkStartX = randomNumber(0, (mapSizeX - chunkSizeX) / chunkSizeX) * chunkSizeX;
        chunkStartY = randomNumber(0, (mapSizeY - chunkSizeY) / chunkSizeY) * chunkSizeY;
        
        for(int j = 0; j < chunkSizeX; ++j)
        {
            for(int k = 0; k < chunkSizeY; ++k)
            {
                if(randomNumber(1, 100) <= resourceChunkResourceChance)
                {   
                    mapBlockTypes[chunkStartX + j][chunkStartY + k] = resourceChunkTypes[i];
                }
            
            }
        }
        
    }

    //CREATE THE MAP BASED ON mapBlockTypes
    for(int iX = 0; iX < sizeX; ++iX)
    {
        
        for(int iY = 0; iY < sizeY; ++iY)
        {
            static std::vector<C_Block>::iterator iT = map.begin();

            static int blockSizeScaledW = 64 * SCALE_W;
            static int blockSizeScaledH = 64 * SCALE_H;
            static long bNum = 0;
           // m1::androidLog("Before map.push_back");
            map.push_back(C_Block());
            //m1::androidLog("After map.push_back");
            iT = map.end()-1;

            blockSizeScaledW = iT->GetW();
            blockSizeScaledH = iT->GetH();

            iT->InitBlock(iX * blockSizeScaledW, iY * blockSizeScaledH, CharToBlockType(mapBlockTypes[iX][iY]) );

            ++bNum;

            std::string s = "Generating Block Nr: " + m1::to_string(bNum); 
            m1::androidLog( s.c_str() );
            
            
        }
        
    }
    
}

void C_Map::SaveMap(int slot){
    
    std::string slot_s = "saveSlot" + m1::to_string(slot) + ".txt";
    SDL_RWops* saveMap = SDL_RWFromFile(slot_s.c_str(), "w");
    
    //Write Map Size in File
    
    m1::SDL_WriteChar(saveMap, "x");
    
    m1::SDL_WriteChar( saveMap, m1::to_string(mapSizeX).c_str() );
    
    m1::SDL_WriteChar(saveMap, "y");
    
    m1::SDL_WriteChar( saveMap, m1::to_string(mapSizeY).c_str() );
    
    for(std::vector<C_Block>::iterator i = map.begin(); i<map.end();i++){
        
        static long blockNum = 0;
        static int j = 1;
        
        m1::SDL_WriteChar(saveMap, "X");

        m1::SDL_WriteChar( saveMap, m1::to_string( i->GetX() ).c_str() );
  
        m1::SDL_WriteChar( saveMap, "Y" );

        m1::SDL_WriteChar( saveMap, m1::to_string( i->GetY() ).c_str() );

        m1::SDL_WriteChar(saveMap, "t");

        m1::SDL_WriteChar(saveMap, i->GetBlockType() );
        
        m1::SDL_WriteChar(saveMap, ";");
        
        if(j==10){

            m1::SDL_WriteChar(saveMap, "\n");
            j=1;

        }

        ++blockNum;
        ++j;

    }

    SDL_RWclose(saveMap);
   
}



void C_Map::LoadMap(int loadSlot){
    
    map.clear();
    
    std::string slot_s = "saveSlot" + m1::to_string(loadSlot) + ".txt";
    SDL_RWops* loadMap = SDL_RWFromFile(slot_s.c_str(), "r");

    bool X = false, Y = false, x = false, y = false, t = false, semikolon = false;

    bool readblockType = false;
    bool readXCoordinate = false;
    bool readYCoordinate = false;
    bool readMapSizeX = false;
    bool readMapSizeY = false;

    bool enableInit = false;

    std::string mapSizeXString;
    std::string mapSizeYString;
    std::string loadedXCoordinateString;
    std::string loadedYCoordinateString;

    long savedMapSizeX = 0;
    long savedMapSizeY = 0;

    long savedBlockCoordinateX = 0;
    long savedBlockCoordinateY = 0;

    int savedBlockType;
    
    char c[1];
    
    //WHILE fstream loadMap gets the character from the file
    while(SDL_RWread(loadMap, c, 1, 1 ) != 0){

        switch(c[0]){

            case 'x': x = true; break;
            case 'y': y = true; break;
            case 'X': X = true; break;
            case 'Y': Y = true; break;
            case 't': t = true; break;
            case ';': semikolon = true; break;

        }

        if(x == true){

            readMapSizeX = true;
            x = false;


        }

        if(y == true){

            readMapSizeY = true;
            y = false;


        }

        if(X == true){

            readXCoordinate = true;
            X = false;


        }

        if(Y == true){

            readYCoordinate = true;
            Y = false;


        }

        if(t == true){

            readblockType = true;
            t=false;


        }

        //IF THE CHARACTER IS A SEMIKOLON, THE NEXT BLOCK WILL BE READ
        if(semikolon==true){

            map.push_back(C_Block());
            enableInit=true;
            semikolon=false;

            mapSizeXString.clear();
            mapSizeYString.clear();
            loadedXCoordinateString.clear();
            loadedYCoordinateString.clear();


        }

        //READ MAPSIZE X FROM FILE
        if(readMapSizeX==true && ( c[0] != 'y' ) && ( c[0] != 'x') ){

            mapSizeXString.push_back(c[0]);


        }

        else if ( readMapSizeX == true && ( c[0] == 'y') ){

            savedMapSizeX = m1::stol(mapSizeXString);
            readMapSizeX = false;

        }

        //READ MAPSIZE Y FROM FILE

        if(readMapSizeY==true && ( c[0] != 'X') && ( c[0] != 'y' )){

            mapSizeYString.push_back(c[0]);


        }

        else if ( readMapSizeY == true && ( c[0] == 'X' ) ){

            savedMapSizeY = m1::stol(mapSizeYString);
            //std::cout<<"Mapsize X: "<<savedMapSizeX<<" Mapsize Y: "<<savedMapSizeY<<std::endl;
            readMapSizeY = false;

        }

        //READ X COORDINATE FROM THIS BLOCK FROM THE FILE
        if(readXCoordinate==true &&( c[0] != 'Y') && ( c[0] != 'X' ) ){

            loadedXCoordinateString.push_back(c[0]);

        }

        else if(readXCoordinate==true && ( c[0] == 'Y')){

            savedBlockCoordinateX = m1::stol(loadedXCoordinateString);
            readXCoordinate = false;

        }

        //READ X COORDINATE FROM THIS BLOCK FROM THE FILE

        if(readYCoordinate==true && ( c[0] != 't') && ( c[0] != 'Y' )){


            loadedYCoordinateString.push_back(c[0]);

        }

        else if(readYCoordinate==true && ( c[0] == 't') ){

            savedBlockCoordinateY = m1::stol(loadedYCoordinateString);
            readYCoordinate = false;

        }

        if(readblockType==true && ( c[0] != ';') && ( c[0] != 't' )){

            savedBlockType = c[0] - '0';
            readblockType = false;

        }

        //Sync the loaded with blockMap;
        e_BlockType castedBT;
        
        if(savedBlockType == 0)
        {
            castedBT = e_BlockType::Grass;
        }    
        
        else if(savedBlockType == 1)
        {
            castedBT = e_BlockType::Coal;
        }       
        
        else if(savedBlockType == 2 )
        {
            castedBT = e_BlockType::Iron;
        }
        
        if(enableInit==true){
            
            static long initLoop = 0;
            
            std::vector<C_Block>::iterator iT = map.begin();
            
            
            iT += initLoop;
            
            
            if(iT==nullptr){
                
                m1::androidLog("Iterator nullptr Map.cpp 304");
                //std::cout<<"NULLPTR iT"<<std::endl;
                //std::cout<<"LOOP NUM: "<<initLoop<<std::endl;
                //std::cout<<"BLOCKMAP SIZE: "<<blockMap.size()<<std::endl;

            }
            
            if(map.size() >= 1){
                
                //std::cout<<"LOOPNUM: "<<initLoop<<" BlockMap Size: "<<blockMap.size()<<" InitX: "<<savedBlockCoordinateX<<" InitY: "<<savedBlockCoordinateY<<std::endl;
                
                iT->InitBlock(savedBlockCoordinateX, savedBlockCoordinateY, castedBT);
                
            }
            
            enableInit = false;
            ++initLoop;
            
        }

    }

    SDL_RWclose(loadMap);
}


