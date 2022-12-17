#pragma once

#ifndef LEVEL_H
#define LEVEL_H

#include "GameState.h"
#include "Play.h"
#include "../gui/Button.h"
#include "../time/Timer.h"
class Level : public GameState {
    public:
        Level(){};
        void Events();
        virtual bool Init();
        virtual bool Exit();
        virtual void Update(float dt);
        virtual void Render();
        static Level* GetInstance(){
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new Level();
        }
        static void SetOpen (std::string st){
            open = true;
        }
        void ChangeMap();
        
        
        TimerID timer;
        Uint32 getTime(){
           return timeD;
        }
        std::string AddLevelStr(bool add);
        static void OpenMenu(std::string str="");
        static void PauseGame();
        std::vector<GameObject*> m_gameObjects;
        std::vector<GameObject*> m_guiObjects;
        static bool open;

        Uint32 timeD = 0; 
        Map* m_LevelMap;
        Label* text;
        Label* text1;
        Button* menu;


    protected: 
        static Level* s_Instance;


};


#endif