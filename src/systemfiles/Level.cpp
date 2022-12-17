#include "Level.h"
#include <math.h>
#include <iomanip>
#include <sstream>
Level* Level::s_Instance = nullptr;
bool Level::open = false;
Uint32 incr(Uint32 interv, void* data){
    Level::GetInstance()->timeD += 1;
    return 1000;
}
bool Level::Init(){
    if (m_guiObjects.size() == 0){
     std::string mapID = Play::GetInstance()->mapName;
        if (!MapParser::GetInstance()->Load(mapID, "assets/maps/" + mapID + ".tmx")){
            std::cout << "Unable to load map!";
        }
        m_LevelMap = MapParser::GetInstance()->GetMaps(mapID);
        MapChunk* collisionLayer = (MapChunk*)m_LevelMap->GetMapChunks().back();
        CollisionHandler::GetInstance()->SetCollisionMap(collisionLayer->GetTileMap(),32);

        int tSize = 32;
        int width = collisionLayer->GetWidth()*tSize;
        int height = collisionLayer->GetHeight()*tSize;

        Viewport::GetInstance()->SetSceneLimit(width,height);

        SDL_Color white = {255,255,255,255};
        std::string e = Play::GetInstance()->mapName;
        std::string b = AddLevelStr(false);
        Uint32 time = getTime(); // seconds
        timer = Timer::GetInstance()->StartTimer(500, incr, (void*)"HI");
 
        text = new Label(SCREEN_WIDTH/2, 32 ,118,32, "Level " + b.substr(5, e.npos), "Comic Sans MS", white);
        text1 = new Label(SCREEN_WIDTH/2, 70 ,118,32, "Time: 00: 00", "Comic Sans MS", white);
        menu = new Button((SCREEN_WIDTH/2) - 100,50,75,50, SetOpen, {"button","buttonhover","button"},"Menu");
        m_guiObjects.push_back(text);
        m_guiObjects.push_back(text1);
        m_guiObjects.push_back(menu);
    }
    Properties* propChar = new Properties("player",5,5,160,160);
    MainChar* player = new MainChar(propChar);
    m_gameObjects.push_back(player);
    Viewport::GetInstance()->SetTarget(player->GetOrigin());

// 138x57 img
   

    /*m_guiObjects.push_back(selectLevelButton);

    m_guiObjects.push_back(settingsButton);*/
    return true;
}

void Level::Render(){
    TextureManager::GetInstance()->Draw("bg",0,0,2100,1050,1,1,0.05);

    m_LevelMap->Render();

    for (auto gameobj : m_gameObjects){
        gameobj->Draw();
    }

    for (auto object : m_guiObjects){
        object->Draw();
    }
    SDL_Rect cam = Viewport::GetInstance()->GetViewBox();

    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(),nullptr,&cam,nullptr);
}

void Level::Update(float dt){
    Events();
    float dti =  Timer::GetInstance()->getDeltaTime();
 //   time += (int)dti;
    
    std::ostringstream oss;
    oss << std::setprecision(8) << std::noshowpoint << floor(timeD/60);
    std::string secs = (timeD < 60) ? (std::to_string(timeD)) : (std::to_string(timeD % 60));
    std::string minutes = (timeD < 60) ? "00" : (oss.str());

    oss.str("");
    oss.clear();
    if (minutes.size() == 1){
         minutes.push_back(minutes[0]);
         minutes[0] = '0';
    } 
    if (secs.size() == 1){
        secs.push_back(secs[0]);
        secs[0] = '0';
    }
    text1->SetLabelText("Time: " +  minutes + " : " + secs, "Comic Sans MS");
    for (auto i : m_gameObjects){
        i->Update(dti);
    }   

    for (auto i : m_guiObjects){
        i->Update(dti);
    }
    Viewport::GetInstance()->Update(dti);
    m_LevelMap->Update();
}

void Level::Events(){
    if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_M) || open == true){
        open = false;
        OpenMenu();
    }
}


bool Level::Exit(){
    if (m_LevelMap){
        m_LevelMap->Clean();
    }
    if (timer){
        Timer::GetInstance()->RemoveTimer(timer);
    }

    timeD = 0;
    for (auto i : m_gameObjects){
        i->Clean();
        delete i;
    }

    for (auto i : m_guiObjects){
        i->Clean();
        delete i;
    }
    m_gameObjects.clear();
    m_gameObjects.shrink_to_fit();
    m_guiObjects.clear();
    m_guiObjects.shrink_to_fit();

    TextureManager::GetInstance()->ParseTexture("assets/textures.tml");
    return true;

}

void Level::OpenMenu(std::string str){
    Level::GetInstance()->Exit();
    std::cout << "Exited!\n";
    Engine::GetInstance()->changeState(Menu::GetInstance());

    Menu::GetInstance()->Init();
}
std::string Level::AddLevelStr(bool add){
    if (Play::GetInstance()->mapName != ""){
        std::string substrD = Play::GetInstance()->mapName.substr(5, Play::GetInstance()->mapName.npos);
        int id = std::stoi(substrD);
       /* if (add){ // currently only 2 MAP (trol)
            bool canEnter = MapParser::GetInstance()->CanEnterMap("assets/maps/" + std::to_string(id+1) + ".tmx");
            if (canEnter){
                id += 1;
                std::cout << id << "hi \n";

            } else {
                id = 1;
            }

        }*/
        if (id < 12 && add){ // currently only 12 MAP (trol)
            id += 1;

        } else if (add){
            id = 1;
        }
 
        std::string newLevelName = "level"; 

        std::string string2 = std::to_string(id);

        std::stringstream ss;

        ss << newLevelName << string2;

        std::string rval = ss.str();
        ss.str("");
        ss.clear();


        return rval;
    } else {
        return "level1";
    }
}
void Level::ChangeMap(){
     std::string mapID = Play::GetInstance()->mapName;
     if (mapID != ""){
        if (m_LevelMap){
            m_LevelMap->Clean();
        }

        timeD = 0;

        if (timer == NULL){
            timer = Timer::GetInstance()->StartTimer(500, incr, (void*)"HI");
        }
        
        if (!MapParser::GetInstance()->Load(mapID, "assets/maps/" + mapID + ".tmx")){
            std::cout << "Unable to load map!";
        }
        m_LevelMap = MapParser::GetInstance()->GetMaps(mapID);
        MapChunk* collisionLayer = (MapChunk*)m_LevelMap->GetMapChunks().back();
        CollisionHandler::GetInstance()->SetCollisionMap(collisionLayer->GetTileMap(),32);

        int tSize = 32;
        int width = collisionLayer->GetWidth()*tSize;
        int height = collisionLayer->GetHeight()*tSize;

        Viewport::GetInstance()->SetSceneLimit(width,height);

        SDL_Color white = {255,255,255,255};
        
        std::string b = AddLevelStr(false);
        std::string e = Play::GetInstance()->mapName;
        if (m_guiObjects.size() == 0 && menu == nullptr && text == nullptr && text1 == nullptr){
        text = new Label(SCREEN_WIDTH/2, 32 ,118,32, "Level " + b.substr(5, e.npos), "Comic Sans MS", white);
        text1 = new Label(SCREEN_WIDTH/2, 70 ,118,32, "Time: xx: xx", "Comic Sans MS", white);
        menu = new Button((SCREEN_WIDTH/2)-100,50,75,50, SetOpen, {"button","buttonhover","button"},"Menu");

        m_guiObjects.push_back(text);
        m_guiObjects.push_back(text1);
        m_guiObjects.push_back(menu);

        } else {
            // already exists
            text->SetLabelText("Level " + b.substr(5,e.npos), "Comic Sans MS");
            text1->SetLabelText("Time: xx: xx", "Comic Sans MS");
        }
        

    }
}
