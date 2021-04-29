//
//  Particle.hpp
//  SDL Basic App
//
//  Created by Jan Michael Austria on 4/23/21.
//  Copyright © 2021 Jan Michael Austria. All rights reserved.
//

#ifndef Particle_h
#define Particle_h

namespace caveofprogramming {
    struct Particle{
        //member are public by default in structs
        //what do we need, manip freely, then just round off
        //need to change gradually, just cast to the nearest int of pixel valu
        double m_x;
        double m_y;
        //normall would need to supply get methoed for x and y, but make public, breaks encapsulation
        /*
        double m_xspeed; //need[-1,1]
        double m_yspeed;
        */
    private:
        double m_speed;
        double m_direction;
    private:
        void init();
    public:
        Particle();
        void update(int interval); // update positions ofparticles
        virtual ~Particle();
    };
    
}

#endif /* Particle_hpp */
