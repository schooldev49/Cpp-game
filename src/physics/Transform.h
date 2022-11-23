#pragma once


#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector2D.h"
class Transform {
    public: 
        float X, Y;
        Transform(float x=0, float y=0):X(x), Y(y){};
    private: 
        inline void TranslateX(float x){X+=x;};
        inline void TranslateY(float y){Y+=y;};
        inline void Translate(Vector2D v){X += v.X; Y+=v.Y;};
        
};


#endif