#include "CollisionHandler.h"
#include "../systemfiles/Play.h"
CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler(){};

void CollisionHandler::SetCollisionMap(TileMap map, int tSize){
    m_CollisionLayer = (MapChunk*)Level::GetInstance()->m_LevelMap->GetMapChunks().back();
    m_colTileMap = m_CollisionLayer->GetTileMap();

    m_tilesize = tSize;

    m_mapHeight = m_colTileMap.size();
    m_mapWidth = m_colTileMap[0].size();
}

bool CollisionHandler::checkCollision(SDL_Rect a, SDL_Rect b){
    bool x_Overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool y_Overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return (x_Overlaps && y_Overlaps);
}

std::string CollisionHandler::MapCollision(SDL_Rect a){
    const int tSize = 32;
    const int rowCount = 20;
    const int colCount = 100;

    int leftTile = a.x/tSize;
    int rightTile = (a.x + a.w)/tSize;

    int topTile = a.y/tSize;
    int bottomTile = (a.y + a.h)/tSize;

    if (leftTile < 0) leftTile = 0;
    if (rightTile > colCount) rightTile = colCount;

    if (topTile < 0) topTile = 0;
    if (bottomTile > rowCount) bottomTile = rowCount;

    for (int i = leftTile; i <= rightTile; ++i){
        for (int j = topTile; j <= bottomTile; ++j){
            if (m_colTileMap[j][i] > 0){
                if (m_colTileMap[j][i] == 33){
                    // key
                    
                    return "key";
                } else if (m_colTileMap[j][i] == 34){
                    // spike

                    return "fire";
                }
                return "platform";
            }
        }
    }
    return "notColliding";

}