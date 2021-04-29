//
//  Particle.cpp
//  SDL Basic App
//
//  Created by Jan Michael Austria on 4/23/21.
//  Copyright © 2021 Jan Michael Austria. All rights reserved.
//

#include "Particle.h"
#include <stdlib.h>
#include <math.h>

namespace caveofprogramming {

    Particle::Particle(){
        //stuff
        /*init anothr way
        m_x = ((2.0*rand())/RAND_MAX) -1; //want -1 to plus 1
        m_y = ((2.0*rand())/RAND_MAX) -1;
        */
        this->m_x = 0;
        this->m_y = 0;
        /*
        m_xspeed = 0.001*((2.0*rand() / RAND_MAX)-1); //need[-1,1]
        m_yspeed = 0.001*((2.0*rand() / RAND_MAX)-1);
        
        m_direction = (2*M_PI*rand())/RAND_MAX;
        m_speed = (0.04*rand())/RAND_MAX;
        
        m_speed *= m_speed;
        */
        init();
    }
    Particle::~Particle(){
        //more stuff
    }
    void Particle::init(){
        this->m_x = 0;
        this->m_y = 0;
        m_direction = (2*M_PI*rand())/RAND_MAX;
        m_speed = (0.04*rand())/RAND_MAX;
        
        m_speed *= m_speed;
    }
    
    void Particle::update(int interval){
        //change position ofparticles
        /*
        m_x += m_xspeed;
        m_y += m_yspeed;
        
        //donte move off edge
        if (m_x < -1.0  || m_x >= 1.0 ){
            m_x = -m_x;
        }
        if (m_y < -1.0  || m_y >= 1.0 ){
            m_y = -m_y;
        }
         */
        m_direction += interval*.0004;
        double x_speed = m_speed*cos(m_direction);
        double y_speed = m_speed*sin(m_direction);
        
        m_x += x_speed*interval;
        m_y += y_speed*interval;
        if (m_x < -1.0 || m_x >= 1.0 || m_y < -1.0  || m_y >= 1.0){
            init();
        }
        //take portion of aprticles on any refresh and re initt
        if (rand() < RAND_MAX/100){
            //1 in every hundrd times ithis is true
            init();
        }
    }
}
