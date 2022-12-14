
<div align="center">

hiiiiiiiiiiii 🙋‍♂️🙋‍♂️
<h1>Jumpy Game</h1>


Hello there! you're probably looking at this section of the internet because you wandered upon it (obviously)! this is a small game i made in my free time for my school's code day challenge. for this project, I wrote the game engine from scratch with [SDL2](https://www.libsdl.org/)/[C++](https://cplusplus.com/), used [tinyxml](https://github.com/vmayoral/tinyxml) to help with tilemap parsing, created the tilemaps with [Tiled](https://www.mapeditor.org/), and used some assets from [Itch](https://itch.io/). (note: the pixelated character/animation was made by me in [Piskelapp](https://www.piskelapp.com/)). i also used [emscripten](https://emscripten.org/) to port the game from C++ into Web Assembly so i could deploy it as a web app. the gui engine (whatever u call it) i made myself.

this also uses the power of service workers/caching to deal with bandwidth limits (bro downloads so much megabytes if i dont cache), the main files that are most memory intensive (index.js and index.wasm) are precached and all other assets are cached once on page load. the service worker should update every once in a while for new updates (probably once a day) but not a lot to prevent netlify from hitting down the site

the game uses my self-made real-time physics engine (if you count 3.25 m/s as gravity as "real time" trol but whatever)

the game is obviously not finished and a lot more features can be added like automatic generation of maps with noise etc but given the limited time allocated for the project this is what i cam up with


</div>
