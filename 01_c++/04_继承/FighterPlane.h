#ifndef __CLIENT_AIRPLAN_H__
#define __CLIENT_ATRPLAN_H__

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
};


} //namespace avdance

#endif //__CLIENT_AIRPLAN_H__
