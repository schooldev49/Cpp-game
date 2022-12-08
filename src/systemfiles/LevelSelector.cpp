#include "LevelSelector.h"
LevelSelector* LevelSelector::s_Instance = nullptr;
Label* LevelSelector::status = nullptr;

bool LevelSelector::Init(std::string mapName){
    // draw GUI
    // each row has 5 levels, and there are 10 columns
    int count = 1;
    std::stringstream ss;
    for (int i=1; i<=10; i++){
        for (int j=1; j<=5; j++){
             ss << count;
             Button* button = new Button((50*j) + 20, (50*i) + 20, 50, 50, clickCallbackHandler, {"button","buttonhover","button"}, ss.str());
             ss.str("");
             ss.clear();
             m_guiObjects.push_back(button);
             count++;
        }
    }
    SDL_Color color = {255,255,255,255};
    status = new Label(125,570,350,100, "Selected level: 1", "Comic Sans MS", color);
    Button* confirm = new Button(150,590, 75,50, clickCallbackHandler2, {"button","buttonhover","button"}, "Confirm");
    m_guiObjects.push_back(confirm);
    m_guiObjects.push_back(status);
}

void LevelSelector::Render(){
    // call GUI rendering functions
    TextureManager::GetInstance()->Draw("bg",0,0,2100,1050,1,1,0.05);
    for (auto i : m_guiObjects){
        i->Draw();
    }
}


void LevelSelector::Update(float dt){
    // call GUI updating functions
    float dti = Timer::GetInstance()->getDeltaTime();
    for (auto i : m_guiObjects){
        i->Update(dti);
    }
}

void LevelSelector::clickCallbackHandler(std::string mapName){
    // handle button press.
    std::cout << mapName << " is cool\n";
    std::string conc = "level";

    conc += mapName;
    std::cout << "wow, " << conc << "\n";
    if (MapParser::GetInstance()->CanEnterMap("assets/maps/" + conc + ".tmx")){
        Play::GetInstance()->setMapName(conc);
        SDL_Color color = {255,255,255,255};
        status->SetTextColor(color);
        status->SetLabelText("Selected level: " + mapName,"Comic Sans MS");
    } else {
        SDL_Color color = {229, 11, 11, 204};
        status->SetTextColor(color);
        status->SetLabelText("Error: You are not allowed to enter level (doesn't exist yet or you didn't beat levels before)", "Comic Sans MS");
    }


}

void LevelSelector::clickCallbackHandler2(std::string mapName){
    // change into MAP.
    LevelSelector::GetInstance()->Exit();
    Menu::GetInstance()->startGame();
}

void LevelSelector::Events(){

}


bool LevelSelector::Exit(){
    // clean objects
 /*   for (auto i : m_guiObjects){
        i->Clean();
        delete i;
    }*/ // DONT DELETE SO MUCH

    return true;
}
