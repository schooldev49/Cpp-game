#define SDL_MAIN_HANDLED 1

#include <stdio.h>

#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "systemfiles/Engine.h"
#include "graphics/TextureManager.h"
#include "time/Timer.h"
Engine* eng = Engine::GetInstance();


#ifdef __EMSCRIPTEN__
    #include <emscripten.h>

void loop(){
    /*if (eng->isRunning() == false){
        //eng->Clean();
        //emscripten_cancel_main_loop();
       // return;
    }*/
    eng->Events(); 
    eng->Update();
    eng->Render();
    Timer::GetInstance()->Tick();
    SDL_Delay(0);
   
}
#endif


extern "C" {
int main(void){
    
    
    if (SDL_Init(SDL_INIT_VIDEO) == 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0){
        printf("success!\n");
    } else {
        std::cout << "error" << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    };
    static Engine* engine = Engine::GetInstance();
    static Timer* timer = Timer::GetInstance();
    engine->Init();
    engine->setRunning(true);
    SDL_Delay(0);
    /*while (engine->isRunning()){
        engine->Events(); 
        engine->Update();
        engine->Render();
        timer->Tick();
        SDL_Delay(0);
    }*/
    #ifdef __EMSCRIPTEN__
        SDL_Delay(0);
        emscripten_set_main_loop(loop,0,1);
    #endif 
    #ifndef __EMSCRIPTEN__
        while (engine->isRunning()){
            engine->Events(); 
            engine->Update();
            engine->Render();
            timer->Tick();
            SDL_Delay(0);
        }
        engine->Clean();

    #endif
    return 0;
   /* SDL_Window *window = SDL_CreateWindow("Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == NULL){
        std::cout << "Could not create window! Erorr " << SDL_GetError() << "\n"; 
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,0);

    SDL_Event windowEvent; 
    while(true){
        if (SDL_PollEvent(&windowEvent)){
            if (windowEvent.type == SDL_QUIT){
                break;
            }
            if (SDL_MOUSEMOTION == windowEvent.type){
                int x, y;
                SDL_GetMouseState(&x,&y);

            }
            if (SDL_MOUSEBUTTONDOWN == windowEvent.type){
                if (SDL_BUTTON_LEFT == windowEvent.button.button){
                    changeColor(renderer,26,100,105,0.8);

                }
            } 
            if (SDL_KEYDOWN == windowEvent.type){
               if (SDLK_w == windowEvent.key.keysym.sym){
                  changeColor(renderer,86,194,145,0.8);

               } else if (SDLK_a == windowEvent.key.keysym.sym){
                  changeColor(renderer,86,100,145,0.8);
               }
               else if (SDLK_s == windowEvent.key.keysym.sym){
                  changeColor(renderer,96,100,145,0.8);
               } else if (SDLK_d == windowEvent.key.keysym.sym){
                  changeColor(renderer,56,100,145,0.8);
               }

            } else if (SDL_KEYDOWN == windowEvent.type){
                std::cout << "key up" << "\n";
                changeColor(renderer,86,194,145,0.8);
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;*/
}
}
// emscripten_set_main_loop