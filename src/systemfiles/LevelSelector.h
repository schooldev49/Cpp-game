#pragma once

#ifndef LEVELSELECTOR_H
#define LEvELSELECTOR_H

#include "Play.h"
#include "GameState.h"

class LevelSelector : public GameState {
    public:
        LevelSelector(){};
        virtual bool Init();
        virtual bool Exit();

        virtual void Update(float dt);
        virtual void Render();
        void Events();
        static LevelSelector* GetInstance(){
            return s_Instance = (s_Instance != nullptr) ? s_Instance : new LevelSelector();
        }
        static void clickCallbackHandler(std::string mapName);
        static void clickCallbackHandler2(std::string mapName);
        std::vector<GameObject*> m_guiObjects;
        static Label* status;
    protected:
        static LevelSelector* s_Instance;
};



#endif