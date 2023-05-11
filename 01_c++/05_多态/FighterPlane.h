#ifndef __FIGHTERPLANE_H__
#define __FIGHTERPLANE_H__

#include<iostream>
#include "AirPlane.h"

namespace avdance {
class FighterPlane:public AirPlane {
    public:
        FighterPlane(){
            weapons = 1;
        }
        ~FighterPlane(){
        }
    private:
        int weapons;
    public:
        void setWeapons(int w);
        int getWeapons();
    public:
        virtual void fly(){
            std::cout<<"FighterPLane fly ..."<<std::endl;
        }
};


} //namespace avdance

#endif //__CLIENT_AIRPLAN_H__
