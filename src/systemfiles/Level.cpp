#include "Level.h"
Level* Level::s_Instance = nullptr;
bool Level::Init(std::string mapN){

     std::string mapID = Play::GetInstance()->mapName;
      std::cout << mapID << " is loading...\n";
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
        Label* levelText = new Label(SCREEN_WIDTH/2, 32 ,118,32, "Level " + b.substr(5, e.npos), "Comic Sans MS", white);
        Label* levelText2 = new Label(SCREEN_WIDTH/2, 70 ,118,32, "Time: xx: xx", "Comic Sans MS", white);

        m_guiObjects.push_back(levelText);
        m_guiObjects.push_back(levelText2);

    
    Properties* propChar = new Properties("player",100,200,160,160);
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
    if (Input::GetInstance()->getKeyDown(SDL_SCANCODE_M)){
        std::cout << "open menu!\n";
        OpenMenu();
    }
}


bool Level::Exit(){
    if (m_LevelMap){
        m_LevelMap->Clean();
    }
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

void Level::OpenMenu(){
    Level::GetInstance()->Exit();
    std::cout << "Exited!\n";
    Engine::GetInstance()->changeState(Menu::GetInstance());

    Menu::GetInstance()->Init();
}
std::string Level::AddLevelStr(bool add){
    if (Play::GetInstance()->mapName != ""){
        std::string substrD = Play::GetInstance()->mapName.substr(5, Play::GetInstance()->mapName.npos);
        std::cout << "\n" << substrD << "\n";
        int id = std::stoi(substrD);
        std::cout << id << "hi \n";

        if (id < MapCount && add){ // currently only 2 MAP (trol)
            id += 1;
            std::cout << id << "hi \n";

        } 

        std::string newLevelName = "level"; 

        std::string string2 = std::to_string(id);

        std::stringstream ss;

        ss << newLevelName << string2;

        std::string rval = ss.str();
        std::cout << rval << " is the valreal2022\n";
        ss.str("");
        ss.clear();


        return rval;
    }
}
void Level::ChangeMap(){
     std::string mapID = Play::GetInstance()->mapName;
     if (mapID != ""){
        if (m_LevelMap){
            m_LevelMap->Clean();
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
        Label* levelText = new Label(SCREEN_WIDTH/2, 32 ,118,32, "Level " + b.substr(5, e.npos), "Comic Sans MS", white);
        Label* levelText2 = new Label(SCREEN_WIDTH/2, 70 ,118,32, "Time: xx: xx", "Comic Sans MS", white);

        m_guiObjects.push_back(levelText);
        m_guiObjects.push_back(levelText2);

    }
}
