//
//  Swarm.cpp
//  SDL Basic App
//
//  Created by Jan Michael Austria on 4/23/21.
//  Copyright © 2021 Jan Michael Austria. All rights reserved.
//

#include "Swarm.h"

namespace caveofprogramming {
    Swarm::Swarm(){
        //inint pointer
        this->lastTime = 0;
        m_pParticles = new Particle[NPARTICLES];
        
    }
    
    Swarm::~Swarm(){
        //dellacote
        delete []m_pParticles;
        
    }
    void Swarm::update(int elapsed){
        //store time since started and when ran
        int interval = elapsed - lastTime;
        for (int i =0; i < Swarm::NPARTICLES; i++){
            m_pParticles[i].update(interval);
        }
        lastTime = elapsed;
    }
}
