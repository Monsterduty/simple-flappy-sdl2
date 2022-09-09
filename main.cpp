//writed by Monsterduty

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <cstdlib>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

SDL_Window   *window;
SDL_Renderer *myRenderer;
SDL_Surface  *resourse, *optimized, *textAlloc = NULL;
SDL_Texture  *flappyTexture, *tubeTexture, *allTextures, *cartelPointsTexture, *textTexture = NULL;
TTF_Font     *FontPoints;
Mix_Chunk    *flapSound, *crashSound, *pointSound;
Mix_Music    *gameOverMusic;
SDL_Color     black = {0,0,0};

SDL_Rect tubePos, birdPos, birdPart, background, bgPart, ground, gdPart, points, pointsPart, cartelPointsPos;

    int screenWidth = 800, screenHeight = 500, gameOver = false;
    int contadorSalto = 50,contadorTiempo = 0, recorte = 0, tubeHeigthPos = screenHeight, GeneralMovement = screenWidth;
    int cualTuberia[5], movimientoDeTuberia[5] = {800, 1200, 1600, 2000, 2400}, posicionDeCualTuberia = 0;

    double gravedad = 20.0, fuerzaDeGravedad = 5.0,  desaceleracion = 0.1;
    
    bool quit = false, salto = false;

void init(){

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN );
    myRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 128);

};

void loadResources(){

    flappyTexture = IMG_LoadTexture(myRenderer, "resources/image/flappySprites.png");
    tubeTexture = IMG_LoadTexture(myRenderer, "resources/image/tuberia.png");
    allTextures = IMG_LoadTexture(myRenderer, "resources/image/demasStprites.png");
    cartelPointsTexture = IMG_LoadTexture(myRenderer, "resources/image/cartelPoints.png");

    FontPoints = TTF_OpenFont("./resources/font/Flappyfontnumbers-Regular.ttf", 50);
    
    flapSound = Mix_LoadWAV("resources/audio/flap.wav");
    crashSound = Mix_LoadWAV_RW(SDL_RWFromFile("resources/audio/crash.wav", "rb"), 1);
    pointSound = Mix_LoadWAV_RW(SDL_RWFromFile("resources/audio/point.wav", "rb"), 1);
    gameOverMusic = Mix_LoadMUS("resources/audio/gameOver.wav");


};

void dibujarSuelo(int i){
    int width = 165, x = 0;
    x = width * i;

    ground.y = 450;
    ground.x = movimientoDeTuberia[i] - 1002;
    ground.h = 200;
    ground.w = 610;
    gdPart.x = 216;
    gdPart.y =  11;
    gdPart.h =  56;
    gdPart.w = width;
    SDL_RenderCopy(myRenderer, allTextures, &gdPart, &ground);

};

void dibujarFondo(int i){
    int width = 133, x = 0;
    x = width * i;

    background.y = 0;
    background.x = GeneralMovement - 933 + x;
    background.h = screenHeight;
    background.w = screenHeight / 2;
    bgPart.x = 3;
    bgPart.y = 0;
    bgPart.w = width;
    bgPart.h = 256;
    SDL_RenderCopy(myRenderer, allTextures, &bgPart, &background);
    if (GeneralMovement <= 667 ){GeneralMovement = screenWidth;};

};

void crearPersonaje(){

    birdPos.y = gravedad ;
    birdPos.x = 50;
    birdPos.w = 50;
    birdPos.h = 45;
    birdPart.y = 0;
    birdPart.x = recorte;
    birdPart.w = 600;
    birdPart.h = 600;
    SDL_RenderCopy(myRenderer, flappyTexture, &birdPart, &birdPos);
    if (birdPos.y >= 460){ Mix_PlayMusic(gameOverMusic, -1); gameOver = true; };

};

int puntaje = 0, marcador = 0;

void verificacion(){

        int i = 0, f = 0;
        bool check1 = false, check2 = false;
       
        while(i < 5){ 
        if (birdPos.x >= movimientoDeTuberia[i] - 50 && birdPos.x <= movimientoDeTuberia[i] + 100){
            
            puntaje++; check1 = true;

            if (birdPos.y >= cualTuberia[i] - 45 || birdPos.y <= cualTuberia[i] - 155){ check2 = true; }; 
        };

        if (check1 && check2 && !gameOver){
            gameOver = true;
            Mix_PlayChannel(1, crashSound, 0);
            Mix_PlayMusic(gameOverMusic, -1);
        };

        i++;};
    
        if (puntaje == 100){ 

        marcador++;
        puntaje = 0;
        Mix_PlayChannel(1, pointSound, 0);
     };

};

char texto[3];

void enteroACaracter(){

    char a = 0, b = 0, c = 0, test = 0;
    int numero = marcador;
    int i = 0, f = 0, e = 0, print = 1, centPrint = 1;
    while (i < numero + 1){
        
        c = '0' + f;
        
        if (f == 10){ f = 0; c = '0'; b = '0' + print; print++; };
        if (e == 100){ e = 0; a = '0' + centPrint; centPrint++; };
        if (print == 10){ print = 0; };
        
        f++;
        e++;
        i++;
    };
    
    i = 0;
    
    char d[3] = { a,b,c };
 
    if (a == test) { d[0] = b; d[1] = c; d[2] = a; };
    if (b == test) { d[0] = c; d[1] = a; d[2] = b; };
    
    while(i < 3){
    
        texto[i] = d[i];
        
        i++;
    };
};


int puntosPrinter[9];

void puntos(){

    
    textAlloc = TTF_RenderText_Solid(FontPoints, texto, black);
    textTexture = SDL_CreateTextureFromSurface(myRenderer, textAlloc);

    cartelPointsPos.x = screenWidth / 2 - 131;
    cartelPointsPos.y = 0;
    cartelPointsPos.w = 260;
    cartelPointsPos.h = 110;
    SDL_RenderCopy(myRenderer, cartelPointsTexture, NULL, &cartelPointsPos);

    points.x = screenWidth / 2 - textAlloc-> w / 1.5;
    points.y = 20;
    points.h = textAlloc->h;
    points.w = textAlloc->w;
    SDL_RenderCopy(myRenderer, textTexture, NULL, &points);

};

void imprimir(int i){

        tubePos.w = 100;
        tubePos.h = 400;
        tubePos.y = cualTuberia[i];
        tubePos.x = movimientoDeTuberia[i];
        SDL_RenderCopy(myRenderer, tubeTexture, NULL, &tubePos);
        tubePos.y = cualTuberia[i] - 550;
        SDL_RenderCopyEx(myRenderer, tubeTexture, NULL, &tubePos, 180.00, NULL, SDL_FLIP_HORIZONTAL );
        if (movimientoDeTuberia[i] < 100 && movimientoDeTuberia[i] > 50){ verificacion(); };
        movimientoDeTuberia[i] -= 2;
        if ( movimientoDeTuberia[i] < - 0 - 100 ){ movimientoDeTuberia[i] = 2000; };
        
};

void gameOverScreen(){

	SDL_Rect gameOverLogo, gameOverLogoPart;

	gameOverLogoPart.y = 173;
	gameOverLogoPart.x = 152;
	gameOverLogoPart.w = 106;
	gameOverLogoPart.h = 21;
	gameOverLogo.y = screenHeight / 2 - 40;
	gameOverLogo.x = screenWidth / 2 - 200;
	gameOverLogo.w = 400;
	gameOverLogo.h = 80;
	SDL_RenderCopy(myRenderer, allTextures, &gameOverLogoPart, &gameOverLogo);

};

int main(int argc, char* argv[])
{

    init();
    loadResources();
    tubePos.w = 100;
    tubePos.h = 400;

    SDL_Event e;
    srand( time(0) );
    int memoriaDeRecorrido = screenWidth + 200, key = 0;

    while( !quit ){

        contadorTiempo--; GeneralMovement--;

        if ( contadorTiempo <= 0 ){
             contadorTiempo = 80;
             tubeHeigthPos = rand() % 300 + 150;
             cualTuberia[posicionDeCualTuberia] = tubeHeigthPos;
             posicionDeCualTuberia++;
        };
        
        while( SDL_PollEvent( &e ) != 0 ){

            if ( e.type == SDL_QUIT ){
                quit = true;
            };

            if ( e.type == SDL_KEYDOWN ){
                if (key == 1) { }else{
                key = 1;
                Mix_PlayChannel(1, flapSound, 0);
                recorte = 600; salto = true;
                contadorSalto = 30;
                desaceleracion = 0.0;
                };
            };

            if ( e.type == SDL_KEYUP ){ key = 0; };

        };

        if (gameOver){

        	gameOverScreen();
        	SDL_RenderPresent(myRenderer); }else {

    SDL_SetRenderDrawColor(myRenderer, 0x70, 0xC4, 0xCB, 0xFF);
    SDL_RenderClear(myRenderer);

    dibujarFondo(0);
    dibujarFondo(1);
    dibujarFondo(2);
    dibujarFondo(3);
    dibujarFondo(4);
    dibujarFondo(5);
    dibujarFondo(6);
    dibujarFondo(7);
    crearPersonaje();
    imprimir(0);
    imprimir(1);
    imprimir(2);
    imprimir(3);
    imprimir(4);
    dibujarSuelo(0);
    dibujarSuelo(1);
    dibujarSuelo(2);
    dibujarSuelo(3);
    dibujarSuelo(4);
    dibujarSuelo(5);
    verificacion();
    enteroACaracter();
    puntos();

    

    SDL_RenderPresent(myRenderer);

    if(salto){ 
        contadorSalto -= 1;
        gravedad -= fuerzaDeGravedad - desaceleracion ;
        desaceleracion += 0.2;
        if( contadorSalto < 6 ){ recorte = 0; };
        if( contadorSalto < 1 ){ 
            salto = false;
            contadorSalto = 30;
            desaceleracion = 0.1; }; 
    };
    if(!salto){
        gravedad += fuerzaDeGravedad + desaceleracion;
        desaceleracion += 0.2;
        recorte = 1200;};
        };
    };

    SDL_Quit();
    
    return 0;
};
