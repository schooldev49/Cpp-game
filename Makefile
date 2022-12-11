all: 
	g++ -I src/include -L src/lib -o main src/main.cpp src/graphics/TextureManager.cpp src/input/Input.cpp src/systemfiles/Engine.cpp src/player/MainChar.cpp src/time/Timer.cpp src/map/MapChunk.cpp src/map/MapParser.cpp src/tinyxml/tinyxml.cpp src/tinyxml/tinystr.cpp src/tinyxml/tinyxmlerror.cpp src/tinyxml/tinyxmlparser.cpp src/viewport/Viewport.cpp src/physics/CollisionHandler.cpp src/player/SequenceAnim.cpp src/player/CharAnim.cpp src/systemfiles/Menu.cpp src/systemfiles/Play.cpp src/systemfiles/Level.cpp src/systemfiles/LevelSelector.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf


