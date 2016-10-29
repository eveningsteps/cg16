### Сборка под Linux
1. Установка необходимых пакетов: `sudo apt-get install mesa-utils libglfw3-dev libglew-dev libglm-dev`
2. Сборка примера: `g++ example.cpp -lGLEW -lglfw -lGL`

### Сборка под Windows
Поскольку в Windows нет репозиториев и пакетного менеджера, все зависимости понадобится установить вручную.

#### Visual Studio
Руководства есть здесь: [раз](http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/), [два](http://www.learnopengl.com/#!Getting-started/Creating-a-window).

#### MinGW
Чтобы выяснить разрядность компилятора, выполните `g++ -dumpmachine` и посмотрите на первую часть вывода. `i686` означает, что компилятор 32-разрядный, `x86_64` — что 64-разрядный.
Заголовочные файлы (.h, .hpp) каждой из библиотек надо будет скопировать в папку `include`, а сами библиотеки (.a, .dll) — в папку `lib` компилятора.

Ссылки:
* [`glm`](https://github.com/g-truc/glm/releases)
* [`GLFW`](http://www.glfw.org/download.html)
* [`GLEW`](http://glew.sourceforge.net)

Поскольку на официальном сайте GLEW выложены только сборки для Visual Studio, понадобится скачать утилиту `make` (либо воспользоваться уже имеющимся `mingw32-make`) и собрать библиотеку из исходников, после чего скопировать только `lib/libglew32.a`. При этом не забудьте дописать в коде примера **до** включения `GL/glew.h`:
```c
#define GLEW_STATIC
```

Сборка примера: `g++ example.cpp -lglew32 -lglfw3 -lgdi32 -lopengl32`
