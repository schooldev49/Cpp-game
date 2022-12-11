#pragma once
#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include <SDL2/SDL.h>
#include <vector>
#include "../map/MapChunk.h"
#include "../map/Map.h"
#include "../systemfiles/Engine.h"

class CollisionHandler {
    public:
        bool checkCollision(SDL_Rect a, SDL_Rect b);
        std::string MapCollision(SDL_Rect a);
        void SetCollisionMap(TileMap map, int tSize);
        inline static CollisionHandler* GetInstance(){
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionHandler();
        }
        inline int getWidth(){
            return m_mapWidth; 
        }
        inline int getHeight(){
            return m_mapHeight;
        }
        inline int getSize(){
            return m_tilesize;
        }
    protected:
        int m_mapWidth, m_mapHeight, m_tilesize = 0;
        CollisionHandler();
        TileMap m_colTileMap;
        MapChunk* m_CollisionLayer;
        static CollisionHandler* s_Instance;
};

#endif