//
//  Screen.cpp
//  SDL Basic App
//
//  Created by Jan Michael Austria on 4/20/21.
//  Copyright © 2021 Jan Michael Austria. All rights reserved.
//

#include "Screen.h"

namespace caveofprogramming {
    Screen::Screen() : m_window(NULL),m_renderer(NULL),m_texture(NULL),m_buffer1(NULL),m_buffer2(NULL){
        //dont init her
    }

    bool Screen::init(){
        //say whehter it succes
        if (SDL_Init(SDL_INIT_AUDIO)<0){
            return false;
        }
        
        m_window = SDL_CreateWindow("Particle Fire Explosion",
                                              SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,
                                              SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        
        //check to see if window is null or not
        if (m_window==NULL){
            SDL_Quit();
            return false;
        }
        
        m_renderer = SDL_CreateRenderer(m_window, -1,SDL_RENDERER_PRESENTVSYNC);
        //sync rendered to refresh screen rate, to prevent shearing
        
        //need tetgre
        m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
                                                 SDL_TEXTUREACCESS_STATIC,SCREEN_WIDTH,SCREEN_HEIGHT);
        //need to deallocate, alloated to those
        //just destroy it
        if (m_renderer == NULL){
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }
        
        if (m_texture == NULL){
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }
        
        //memeory
        //normally check memory can actually be allocated
        m_buffer1 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
        m_buffer2 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
        
        //write pixel info into buffer
        //can write 255 in hex, also would work
        memset(m_buffer1, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
        memset(m_buffer2, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));
        
        /*
        for (int i = 0; i < (SCREEN_WIDTH*SCREEN_HEIGHT) / 3; i++){
            buffer[i] = 0x0000FFFF;
        }
        */
        return true;
        
    }
    /*
    void Screen::clear(){
        memset(m_buffer1,0,SCREEN_HEIGHT*SCREEN_WIDTH*sizeof(Uint32));
        memset(m_buffer2,0,SCREEN_HEIGHT*SCREEN_WIDTH*sizeof(Uint32));
    }
    */
    
    void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue){
        //this sets an individual pixel
        
        //check pixel if screen
        if (x < 0 || x >= Screen::SCREEN_WIDTH || y < 0 || y >= Screen::SCREEN_HEIGHT){
            return; //note this in in-effcicient, clipped frames do not check for every pixel
        }
        Uint32 color = 0;
        
        color += red;
        color <<= 8;
        color += green;
        color <<=8;
        color += blue;
        color <<=8;
        color += 0xFF; //alpha value, opaque
        
        m_buffer1[(y*SCREEN_WIDTH)+x] = color;
        //format is RGBA
    }
    
    void Screen::update(){
        SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH*sizeof(Uint32));
        //update texture with pixel info in buffer
        SDL_RenderClear(m_renderer);
        SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
        SDL_RenderPresent(m_renderer);
        //need to clean particle buffer somewhere
        
    }
    bool Screen::processEvents(){
        SDL_Event event;
        //keeps going so long as event eneds to be processed
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT ){
                return false;
            }
            
        }
        return true;
        
    }
    void Screen::close(){
        delete []m_buffer1;
        delete []m_buffer2;
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyTexture(m_texture);
        
        SDL_DestroyWindow(m_window); //need to delay
        
        SDL_Quit();
        
    }
    void Screen::boxBlur(){
        //instead of drawing screen directly
        //calculate new sceen with blurred values for all the pixel, need to creat new pizel view and show this creen with wnew calcs
        //wrtie from buffer 2 to buffer 1
        Uint32 *temp = m_buffer1; //need new pointer
        m_buffer1 = m_buffer2; //swap bufferrs to pixel indeo is in buffer two, and drawing to buffer 1
        m_buffer2 = temp;
        //now go through all pixels
        for (int y = 0; y < Screen::SCREEN_HEIGHT; y++){
            for (int x= 0; x < Screen::SCREEN_WIDTH; x++){
                //need color values from pixels
                int redTotal = 0;
                int greenTotal =0;
                int blueTotal = 0;
                for (int row = -1; row <=1;row++){
                    for (int col = -1; col <=1; col++){
                        int currX = x + col;
                        int currY = y + row;
                        //boundary conditions
                        if (currX >= 0 && currX < Screen::SCREEN_WIDTH && currY >= 0 && currY < Screen::SCREEN_HEIGHT){
                            //get color value
                            Uint32 color = m_buffer2[currY*SCREEN_WIDTH + currX];
                            Uint8 red = color >> 24;
                            Uint8 green = color >> 16;
                            Uint8 blue = color >> 8;
                            redTotal += red;
                            greenTotal += green;
                            blueTotal += blue;
                        }
                    }
                }
             
                Uint8 red = redTotal /9;
                Uint8 green = greenTotal/9;
                Uint8 blue = blueTotal/9;
                
                //put back into buffer
                setPixel(x,y,red,green,blue);
                
            }
        }
    }
}
