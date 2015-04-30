#include <GL/freeglut.h>
#include <GL/gl.h>
#include <stdio.h>

#include "Rosalila/system.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

//SDL
#include "SDL2/SDL.h"
#include "Rosalila/RosalilaUtility/RosalilaUtility.h"
#include "Rosalila/RosalilaInputs/RosalilaInputs.h"
#include "Rosalila/RosalilaGraphics/RosalilaGraphics.h"
#include "Rosalila/RosalilaSound/RosalilaSound.h"

#ifdef LINUX
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif

#ifdef WINDOWS
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif

#ifdef OSX
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#endif

int main(int argc, char *argv[])
{
    //Clean the previous log
    clearLog();

    //OpenGL initialization
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

    //Input receiver initialization
    Receiver* receiver = new Receiver();

    //Graphics initialization
    RosalilaGraphics* rosalila_graphics = new RosalilaGraphics();
    rosalila_graphics->video(rosalila_graphics);

    //Sound initialization
    Sound*sound = new Sound();
    sound->addSound("sonido",assets_directory+"sound.ogg");


    //Texture load
    Image *image=rosalila_graphics->getTexture(assets_directory+"image.png");

    float x=0;
    float y=0;
    float scale=1;
    float rotation=0;
    bool horizontal_flip=false;
    int red_effect=255;
    int green_effect=255;
    int blue_effect=255;
    int alpha_effect=255;
    bool red_effect_activated=false;
    bool green_effect_activated=false;
    bool blue_effect_activated=false;
    bool alpha_effect_activated=false;

    while(true)
    {
        rosalila_graphics->draw2DImage
        (   image,
            image->getWidth(),image->getHeight(),
            x,y,
            scale,
            rotation,
            horizontal_flip,
            0,0,
            Color(red_effect,green_effect,blue_effect,alpha_effect),
            0,0,
            false);

        if(receiver->isKeyDown(SDLK_ESCAPE))
            break;

        if(receiver->isKeyDown(SDL_SCANCODE_UP))
            y-=0.5;
        if(receiver->isKeyDown(SDL_SCANCODE_DOWN))
            y+=0.5;
        if(receiver->isKeyDown(SDL_SCANCODE_LEFT))
            x-=0.5;
        if(receiver->isKeyDown(SDL_SCANCODE_RIGHT))
            x+=0.5;

        if(receiver->isKeyDown('r'))
            rotation+=0.5;

        if(receiver->isKeyDown('s'))
            scale+=0.01;

        if(receiver->isKeyDown('t'))
            rotation-=0.5;

        if(receiver->isKeyDown('d'))
            scale-=0.01;

        if(receiver->isKeyDown('h'))
            horizontal_flip=true;
        else
            horizontal_flip=false;


        if(receiver->isKeyPressed(SDLK_SPACE))
            sound->playSound("sonido");

        if(receiver->isKeyDown('1'))
        {
            red_effect+=10;
            if(red_effect>255)
                red_effect=0;
        }else
        {
            red_effect=255;
        }

        if(receiver->isKeyDown('2'))
        {
            green_effect+=10;
            if(green_effect>255)
                green_effect=0;
        }else
        {
            green_effect=255;
        }

        if(receiver->isKeyDown('3'))
        {
            blue_effect+=10;
            if(blue_effect>255)
                blue_effect=0;
        }else
        {
            blue_effect=255;
        }

        if(receiver->isKeyDown('4'))
        {
            alpha_effect+=10;
            if(alpha_effect>255)
                alpha_effect=0;
        }else
        {
            alpha_effect=255;
        }

        receiver->updateInputs();
        rosalila_graphics->updateScreen();
    }


    return 0;
}
