#pragma once 

#ifndef MENU_H
#define MENU_H
#include <SDL2/SDL.h>
#include "GameState.h"
#include "Play.h"
class Menu : public GameState {
    public:
        Menu();
        virtual bool Init();
        virtual bool Exit();
        virtual void Update(float dt);
        virtual void Render();
        static Menu* GetInstance(){
           return s_Instance = (s_Instance != nullptr) ? s_Instance : new Menu(); 
        }

        static void startGame(std::string tx = "");
        static void settings();
        static void levelSelector(std::string ti = "");
        static void quit();

    protected:
      
        std::vector<GameObject*> m_guiObjects;
        static Menu* s_Instance;

};

#endif