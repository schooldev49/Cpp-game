#include "MapParser.h"
#include "MapChunk.h"
#include <vector>
#include <string>
#include <sstream>
#include <istream>
#include <iostream>
MapParser* MapParser::s_Instance = nullptr;

bool MapParser::Load(std::string id, std::string source){
    if (!Parse(id,source)){
        std::cout << "Nope!\n";
        return false;
    }
    std::cout << "Parsed map!\n";
    return true;
}

void MapParser::Clean(){
    std::map<std::string, Map*>::iterator it;
    for (it=m_mapDict.begin(); it != m_mapDict.end(); it++){
        it->second = nullptr;
    }
    m_mapDict.clear();

}
bool MapParser::Parse(std::string id, std::string source){
    std::cout << "Parsing " << id << " from " << source << " ...\n";
    TiXmlDocument xml;
    xml.LoadFile(source);
    if (xml.Error()){
        return false;
    }
    std::cout << "Loaded file!\n";

    TiXmlElement* root = xml.RootElement();

    int rowcount, colcount, tilesize = 0;


    root->Attribute("width",&colcount);
    root->Attribute("height",&rowcount);
    root->Attribute("tilewidth",&tilesize);


    TilesetList tilesets;
    Map* mape = new Map();
    for (TiXmlElement* e=root->FirstChildElement(); e!=nullptr; e=e->NextSiblingElement()){
        if (e->Value() == std::string("tileset")){
            tilesets.push_back(ParseTileset(e));
        }
        else if (e->Value() == std::string("layer")){
            MapChunk* lay = ParseTileLayer(e,tilesets,tilesize,rowcount,colcount);
            mape->m_MapChunks.push_back(lay);

        }
    }
    m_mapDict[id] = mape;
    return true;
}

Tiles MapParser::ParseTileset(TiXmlElement* ele){
    Tiles tileset;
    tileset.Name = ele->Attribute("name");
    ele->Attribute("firstgid",&tileset.First);
    ele->Attribute("tilecount",&tileset.tileCount);
    tileset.LastID = (tileset.First + tileset.tileCount) - 1;
    ele->Attribute("columns",&tileset.colCount);
    tileset.rowCount = tileset.tileCount / tileset.colCount;

    ele->Attribute("tilewidth",&tileset.tileSize);

    TiXmlElement* image = ele->FirstChildElement();
    tileset.Source = image->Attribute("source");
    return tileset;
}

MapChunk* MapParser::ParseTileLayer(TiXmlElement* ele, TilesetList tilesets, int tilesize, int rowcount, int colcount){
    TiXmlElement* data;
    for (TiXmlElement* e = ele->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement()){
        if (e->Value() == std::string("data")){
            data = e;
            break;
        }
    }
    if (!data){
        std::cout << "we have no data..\n";
    }

   /* for (TiXmlElement* e = data->FirstChildElement(); e!=nullptr; e=e->NextSiblingElement()){
        if (e->Value() == std::string("chunk")){
            ParseChunk(e->GetText()); // ok
        }
    }*/
    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;
    
    TileMap tilemap(rowcount,std::vector<int> (colcount,0));
    std::cout << "rows: " << rowcount << " cols: " << colcount << "\n";
    for (int row = 0; row < rowcount; row++){
        for (int col = 0; col < colcount; col++){
            getline(iss,id,','); // delimiter ",". goes from first char to "," - 0
            // converts
            std::stringstream converter(id);
            converter >> tilemap[row][col];
            if (!iss.good())
                break;
        }
    }
    return (new MapChunk(tilesize,rowcount,colcount,tilemap,tilesets));
}

