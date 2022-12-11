#pragma once
#ifndef BUTTON_H

#define BUTTON_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "../input/Input.h"
#include "../player/GameObject.h"
#include "Label.h"
#include "../graphics/TextureManager.h"

using TextureIdList = std::vector<std::string>;

enum ButtonState {
    NORMAL = 0,
    HOVER = 1,
    PRESSED = 2
};


class Button : public GameObject {
    public:
    //     Properties(std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip=SDL_FLIP_NONE){

        Button(int x, int y, int width, int height, void (*callback)(std::string txt), TextureIdList txtrIds, std::string buttonText=""): GameObject(new Properties(txtrIds[NORMAL],x,y,width,height)){
            m_Transform->X = x;
            m_Transform->Y = y;
            m_Callback = callback;
            m_TextrIds = txtrIds; 
            TextureManager::GetInstance()->QueryTexture(tID, &m_width, &m_height);
            m_Shape = {(int)m_Transform->X, (int)m_Transform->Y, m_width,m_height};

            if (buttonText != ""){
                // draw text
                bT = buttonText;

                SDL_Color color = {12,225,12,204};
                label = new Label(x+10,y+15,x-20,y-25, buttonText, "Comic Sans MS",color);
                
            }
        }

        ~Button(){
            m_TextrIds.clear();
            m_TextrIds.shrink_to_fit();
            if (label){
                label->Clean();
                delete label;
            }
        }
        virtual void Draw() override{
            //     TextureManager::GetInstance()->Draw("bg",0,0,2100,1050,1,1,0.05);
            TextureManager::GetInstance()->Draw(tID, m_Transform->X, m_Transform->Y, m_width, m_height);
            if (label){
                label->Draw();
            }
        }
        virtual void Clean() override {
            for (auto id : m_TextrIds){
                TextureManager::GetInstance()->Drop(id);
            }

            m_TextrIds.clear();
            m_TextrIds.shrink_to_fit();

            if (label){
                label->Clean();
                delete label;
            }
        }

        virtual void Update(float dt) override {
            int x, y = 0;
            SDL_GetMouseState(&x,&y);
            SDL_Point point = {x, y};

            if (SDL_PointInRect(&point,&m_Shape)){
                if (Input::GetInstance()->isDown() && m_isReleased){
                    m_Callback(bT);
                    m_isReleased = false;
                    tID = m_TextrIds[PRESSED];
                } else if (!Input::GetInstance()->isDown()){
                    m_isReleased = true;
                    tID = m_TextrIds[HOVER];
                } 
            } else {
                tID = m_TextrIds[NORMAL];
            }
        } 
        SDL_Rect m_Shape;
        bool m_isReleased;
        std::string bT = "";
        void (*m_Callback)(std::string txt);
        TextureIdList m_TextrIds;
        std::string tID;
        Label* label;
};

#endif