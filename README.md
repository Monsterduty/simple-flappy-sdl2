# simple-flappy-sdl2
a simple flappy bird based game with sdl2

### dependencies:

  * SDL2
  * SDL2_mixer
  * SDL2_image
  * SDL2_ttf
  * Make
  * g++
  
  ### compile:
  
  ```bash
  
  make
  ./flappy
  
  ```
  if you dont have the require SDL libraries, and you are using linux, you can also run
  make withDeps for use the libraries that are included with the project and then create
  a eviroment variable called LD_LIBRARY_PATH for can run the executable
  
  ```bash
  
  make withDeps
  export LD_LIBRARY_PATH=deps/SDL2/lib
  ./flappy
  
  ```
  
