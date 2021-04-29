//
//  main.cpp
//  SDL Basic App
//
//  Created by Jan Michael Austria on 4/15/21.
//  Copyright © 2021 Jan Michael Austria. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <math.h>
#include "Screen.h"
#include <stdlib.h>
#include <time.h>
#include "Particle.h"
#include "Swarm.h"
using namespace std;
using namespace caveofprogramming;

int main(int argc, char *argv[]) {
    
    //seed randome numbner
    srand(time(NULL));
    Screen screen;
    
    if (screen.init() == false){
        cout << "Error initializaing SCL" << endl;
    }

    Swarm swarm;
    
    
    //game loops, GUI interface
    while (true){
        //Update particles
        //Draw Particles
        
        int elapsed = SDL_GetTicks();
        
        //screen.clear();
        
        swarm.update(elapsed);
        
        unsigned char green = (1+sin(elapsed*0.0002))*128; //range for unsigned char is [0,255]
        unsigned char red = (1+sin(elapsed*0.0003))*128;
        unsigned char blue = (1+sin(elapsed*0.0004))*128;
        
        const  Particle *const pParticles = swarm.getparticles();
        for (int i = 0; i < Swarm::NPARTICLES; i++){
            Particle particle = pParticles[i];
            int x = (particle.m_x + 1)*Screen::SCREEN_WIDTH/2; //recall m_x and m_y are between 0 and 1, convert to place on screen
            int y = particle.m_y*Screen::SCREEN_WIDTH/2 + Screen::SCREEN_HEIGHT/2;
            
            
            screen.setPixel(x,y,red,green,blue);
            
            //redrawgin, clear the screen and update positions
        }
        /*
        for (int y=0; y < Screen::SCREEN_HEIGHT; y++){
            for (int x=0; x < Screen::SCREEN_WIDTH; x++){
                screen.setPixel(x,y,red,green,blue);
                //smoothly animate one color transtion to another
                //cycle
                
            }
        }
         */
    
    //implement blue
    screen.boxBlur();
    //draw the screen
    screen.update();
    
    //check for messages/evetns
    if (screen.processEvents()== false){
        break;
        }
    }
    
    //cout << max << endl;

    screen.close();

    return 0;
}
