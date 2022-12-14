#include "Input.h"
#include "../systemfiles/Engine.h"

Input* Input::s_Instance = nullptr;

Input::Input(){
    m_KeyStates = SDL_GetKeyboardState(nullptr);

}

bool Input::getKeyDown(SDL_Scancode key){
    if (m_KeyStates[key] == 1){
        return true;
    }
    return false;
}

void Input::mouseDown(SDL_MouseButtonEvent& b){
    if (b.button == SDL_BUTTON_LEFT){
        isMouseDown = true;
    }
}

void Input::mouseUp(SDL_MouseButtonEvent& b){
    if (b.button == SDL_BUTTON_LEFT){
        isMouseDown = false;
    }
}

void Input::Listen(){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                Engine::GetInstance()->Quit();
            case SDL_KEYDOWN: 
                keyDown();
                break;
            case SDL_KEYUP: 
                keyUp();
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseDown(event.button);
                break;
            case SDL_MOUSEBUTTONUP:
                mouseUp(event.button);
                break;
        }
        SDL_Delay(0);

    }
}

void Input::keyUp(){
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::keyDown(){
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}