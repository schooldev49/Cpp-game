#include "TextureManager.h"
#include "../systemfiles/Engine.h"
#include "../viewport/Viewport.h"
#include "../tinyxml/tinyxml.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename){
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr){
        std::cout << "Failed to load texture " << filename.c_str() << " \n" << IMG_GetError();
        return false;
    }
    Engine* engine = Engine::GetInstance();
    SDL_Texture* texture = SDL_CreateTextureFromSurface(engine->GetRenderer(),surface);

    if (texture == nullptr){
        std::cout << "Failed to load surface " << SDL_GetError() << " \n";
        return false;
    }
    m_TextureMap[id] = texture; 
    return true;
}

void TextureManager::AddFont(std::string id, std::string path, int fontSize){
    m_FontMap.emplace(id, TTF_OpenFont(path.c_str(),fontSize));
}

TTF_Font* TextureManager::GetFont(std::string id){
   
    return m_FontMap[id];
    
}

void TextureManager::QueryTexture(std::string id, int* out_w, int* out_h){
    if (m_TextureMap[id] != nullptr){
        SDL_QueryTexture(m_TextureMap[id],NULL,NULL, out_w, out_h);
    }
}
void TextureManager::Draw(std::string id, int x, int y, int width, int height, float scaleX, float scaleY, float scrollRatio, SDL_RendererFlip flip){
    if (m_TextureMap[id] != nullptr){
    SDL_Rect srcRect = {0,0,width,height};
    Vector2D cam = Viewport::GetInstance()->GetPosition()*scrollRatio;
    SDL_Rect dstRect = {static_cast<int>(x - cam.X),static_cast<int>(y - cam.Y),static_cast<int>(width*scaleX),static_cast<int>(height*scaleY)};
    
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
    }
}


void TextureManager::DrawTile(std::string tid, int tSize, int x, int y, int row, int frame, SDL_RendererFlip flip){

    if (m_TextureMap[tid] != nullptr){
    SDL_Rect srcRect = {tSize*frame, tSize * row, tSize, tSize};

    Vector2D cam = Viewport::GetInstance()->GetPosition();

    SDL_Rect dstRect = {static_cast<int>(x - cam.X),static_cast<int>(y - cam.Y),tSize, tSize};

    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(),m_TextureMap[tid],&srcRect,&dstRect,0,0,flip);
    }
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip){
    if (m_TextureMap[id] != nullptr){
    SDL_Rect srcRect = {width*frame, 0 ,width,height};
    Vector2D cam = Viewport::GetInstance()->GetPosition();
    SDL_Rect dstRect = {static_cast<int>(x - cam.X),static_cast<int>(y - cam.Y),width,height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, 0, flip);

    }
}


void TextureManager::Drop(std::string id){
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean(){
    std::map<std::string, SDL_Texture*>::iterator it;
    for (it=m_TextureMap.begin(); it != m_TextureMap.end(); it++){
        SDL_DestroyTexture(it->second);
    }
    m_TextureMap.clear();
}

bool TextureManager::ParseTexture(std::string source){
    TiXmlDocument xml;
    xml.LoadFile(source);

    if (xml.Error()){
        std::cout << "Failed to load " << source << "\n" << "reason: " << xml.ErrorDesc() << "\n";
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    for (TiXmlElement* e=root->FirstChildElement(); e!=nullptr; e=e->NextSiblingElement()){
        if (e->Value() == std::string("texture")){
            std::string id = e->Attribute("id");
            std::string src = e->Attribute("source");
            Load(id,src);
        }
    }

    return true;
}