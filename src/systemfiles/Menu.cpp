#include "Menu.h"
#include "Engine.h"
#include "../input/Input.h"
#include <iostream>
Menu* Menu::s_Instance = nullptr;

Menu::Menu(){}

bool Menu::Init(){
    if (SDL_GetError()){
        std::cout << "There was an error! " << SDL_GetError(); // this is fake...
    }
    Button* menuButton = new Button(10,10,138,57,startGame,{"button","buttonhover","button"},"Play");
    Button* levelSelectorButton = new Button(10,90,138,57, levelSelector,{"button","buttonhover","button"},"Select level");

    //SDL_Color white = {12,225,12,204};
    //Label* menuLabel = new Label(20,25,118,32, "Play","Comic Sans MS",white);
  //  Button* settingsButton = new Button(10,90,89,32,Level::GetInstance()->OpenMenu,{"button","buttonhover","button"});
    m_guiObjects.push_back(menuButton);
    m_guiObjects.push_back(levelSelectorButton);
    //m_guiObjects.push_back(menuLabel);
    return true;
}




bool Menu::Exit(){
    std::cout << "Exited." << "\n";
    return true;
}

void Menu::Render(){

    for (auto i : m_guiObjects){
        i->Draw();
    }
}

void Menu::Update(float dt){
    float dti =  Timer::GetInstance()->getDeltaTime();
    for (auto i : m_guiObjects){
        i->Update(dti);
    }
   
}

void Menu::startGame(std::string tx){
    // TODO: Open level selector!
    // After opening... return level.
    Engine::GetInstance()->changeState(Level::GetInstance());
    Level::GetInstance()->Init();
}

void Menu::settings(){

}

void Menu::levelSelector(std::string st){
    Engine::GetInstance()->changeState(LevelSelector::GetInstance());
    LevelSelector::GetInstance()->Init();
}

void Menu::quit(){
    
}
