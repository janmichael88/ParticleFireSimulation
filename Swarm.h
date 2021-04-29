//
//  Swarm.hpp
//  SDL Basic App
//
//  Created by Jan Michael Austria on 4/23/21.
//  Copyright © 2021 Jan Michael Austria. All rights reserved.
//

#ifndef Swarm_h
#define Swarm_h

#include "Particle.h"

namespace caveofprogramming {
    class Swarm{
    public:
        const static int NPARTICLES = 5000;
    private:
        Particle *m_pParticles; //dont point anywhere else here
        int lastTime;
        
    public:
        Swarm();
        virtual ~Swarm();
        //returns particl pointer
        const Particle *const getparticles(){
            return m_pParticles; //after returing don't change
        };
        void update(int elapsed);
    };
}

#endif /* Swarm_hpp */
