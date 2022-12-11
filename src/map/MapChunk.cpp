#include "MapChunk.h"
#include "../graphics/TextureManager.h"
#include "../viewport/Viewport.h"
#include <iostream>
typedef unsigned int uint;
MapChunk::MapChunk(int p_tilesize, int p_rowcount, int p_colcount, TileMap p_tilemap, TilesetList p_tilesets): m_tileSize(p_tilesize), m_ColCount(p_colcount), m_rowCount(p_rowcount), m_Tilemap(p_tilemap), m_tileSets(p_tilesets) {
    for (uint i=0; i<m_tileSets.size(); i++){
        TextureManager::GetInstance()->Load(m_tileSets[i].Name,"assets/maps/" + m_tileSets[i].Source);
    }
    
}

void MapChunk::Update(){
    
}

void MapChunk::Render(){
    for (uint i=0; i < m_rowCount; i++){
        for (uint j=0; j < m_ColCount; j++){
            int tileID = m_Tilemap[i][j];
            int temp = tileID;
            if (tileID == 0){
                continue;
            } else {

                int index = 0;
            
                if (m_tileSets.size() > 1){

                    for (uint k=1; k < m_tileSets.size(); k++){
                        if (tileID >= m_tileSets[k].First && tileID <= m_tileSets[k].LastID){
                            tileID = tileID + m_tileSets[k].tileCount - m_tileSets[k].LastID;
                            index = k;
                            break;
                        }
                    }
                }
                Tiles ts = m_tileSets[index];
                int tileRow = tileID/ts.colCount;
                int tileCol = tileID - tileRow*ts.rowCount-1;
                
                if (tileID % ts.colCount == 0){
                    tileRow--;
                    tileCol = ts.colCount - 1;
                }
                TextureManager::GetInstance()->DrawTile(ts.Name,ts.tileSize,j*ts.tileSize, i*ts.tileSize, tileRow, tileCol);
            }
        }
    }
}