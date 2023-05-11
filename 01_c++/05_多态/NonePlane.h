#ifndef __NONEPLANE_H__
#define __NONEPLANE_H__

#include<iostream>
#include "AirPlane.h"

namespace avdance {
class NonePlane:public AirPlane {
    public:
        NonePlane(){
            std::cout<<"NonePlane construct ... "<<std::endl;
            weapons = 1;
        }
        ~NonePlane(){
            std::cout<<"NonePlane destruct ..."<<std::endl;
        }
    private:
        int weapons;
    public:
        void setWeapons(int w);
        int getWeapons();
    public:
        virtual void fly(){
            std::cout<<"NonePlane fly ..."<<std::endl;
        }
};


} //namespace avdance

#endif //__CLIENT_AIRPLAN_H__
