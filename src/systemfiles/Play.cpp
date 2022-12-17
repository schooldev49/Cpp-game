#include "Play.h"
#include <SDL2/SDL.h>
Play* Play::s_Instance = nullptr;

#define m_gameObjects Level::GetInstance()->m_gameObjects


bool Play::Init(){
   TextureManager::GetInstance()->ParseTexture("assets/textures.tml");

   Engine::GetInstance()->getState()->Init();

   return true;
   // m_LevelMap = MapParser::GetInstance()->Load("assets/maps/map.tmx");

}

void Play::Render(){
    SDL_SetRenderDrawColor(Engine::GetInstance()->GetRenderer(),124,218,254,255);
    SDL_RenderClear(Engine::GetInstance()->GetRenderer());
    Engine::GetInstance()->getState()->Render();
    SDL_RenderPresent(Engine::GetInstance()->GetRenderer());
}

void Play::Update(float dt){
    Events();
    float dti = Timer::GetInstance()->getDeltaTime();
    Engine::GetInstance()->getState()->Update(dti);
}

void Play::Events(){

}

bool Play::Exit(){
    Engine::GetInstance()->getState()->Exit();
    
    m_gameObjects.clear();
    TextureManager::GetInstance()->Clean();
    return true;
}
/*
void Play::OpenMenu(){
    Engine::GetInstance()->changeState(new Menu());
}*/ 