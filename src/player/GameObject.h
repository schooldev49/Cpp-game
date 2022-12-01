#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>

#include "Object.h"
#include "../physics/Transform.h"
#include "../physics/Point.h"
#include "string"
struct Properties {
     public:
        Properties(std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip=SDL_FLIP_NONE){
            X = x;
            Y = y;
            Flip = flip;
            Width = width;
            Height = height;
            TextureID = textureID;

        }
        int Width, Height;
        float X, Y;
        std::string TextureID;
        SDL_RendererFlip Flip;
};

class GameObject: public Object {
    public:
        GameObject(Properties* props) {
            // m_TextureID(props->TextureID), m_width(props->Width), m_Height(props->Height), m_Flip(props->Flip) 
            m_TextureID = props->TextureID;
            m_width = props->Width;
            m_height = props->Height;
            m_Flip = props->Flip;
            m_Transform = new Transform(props->X, props->Y);
            float px = props->X + props->Width/2;
            float py = props->Y + props->Height/2;
            m_Origin = new Point(px,py);
        };

        inline Point* GetOrigin(){
            return m_Origin;
        }
        virtual void Draw()=0;
        virtual void Clean()=0;
        virtual void Update(float dt)=0;
    protected:
        Point* m_Origin;
        Transform* m_Transform;
        int m_width, m_height;
        std::string m_TextureID;
        SDL_RendererFlip m_Flip;
};

#endif