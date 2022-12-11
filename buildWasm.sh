
# emcc src/main.cpp -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2 --preload-file assets -o test/index.js
# sleep 5s



emcc -O3 -I src/include -L src/lib src/main.cpp src/graphics/TextureManager.cpp src/input/Input.cpp src/systemfiles/Engine.cpp src/player/MainChar.cpp src/time/Timer.cpp src/map/MapChunk.cpp src/map/MapParser.cpp src/tinyxml/tinyxml.cpp src/tinyxml/tinystr.cpp src/tinyxml/tinyxmlerror.cpp src/tinyxml/tinyxmlparser.cpp src/viewport/Viewport.cpp src/physics/CollisionHandler.cpp src/player/SequenceAnim.cpp src/player/CharAnim.cpp src/systemfiles/Menu.cpp src/systemfiles/ObjectR.cpp src/systemfiles/Play.cpp src/systemfiles/Level.cpp src/systemfiles/LevelSelector.cpp -o test/index.js -sERROR_ON_UNDEFINED_SYMBOLS=0  -s EXPORTED_FUNCTIONS='["_main", "_SDL_CreateRenderer", "_SDL_CreateTextureFromSurface","_SDL_CreateWindow","_SDL_DestroyTexture","_SDL_QueryTexture","_SDL_RenderClear", "_SDL_RenderCopy", "_SDL_RenderCopyEx", "_SDL_RenderDrawRect","_SDL_RenderPresent","_SDL_SetRenderDrawColor"]' -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2 --preload-file assets -g

sleep 10s


