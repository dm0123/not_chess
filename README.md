# Not chess
This is repository for hosting a simple game of pawns.

I'm using [SFML](https://www.sfml-dev.org/) to create base layer of my game. This project is also using slightly modfied event system based on [this](https://www.codeproject.com/Articles/1256352/CppEvent-How-to-implement-events-using-standard-cp) article.
To build the project you need SFML and [CMake](cmake.org) to be installed on your system.

```console
mkdir build && cd build
cmake ../ -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

The compiled project will be placed into build/src/ directory. You will also need to copy assets folder here because stupid me forgot how write install targets for CMake.

Feel free to spam my inbox

<dpolomin@gmail.com>
