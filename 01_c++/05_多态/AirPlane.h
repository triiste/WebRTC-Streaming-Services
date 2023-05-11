#ifndef __AIRPLANE_H__
#define __AIRPLANE_H__

#include<iostream>

namespace avdance {

class AirPlane{

    public:
        AirPlane(){
            wings = 2;
            wheels = 3;
            engines = 1;
        }

        ~AirPlane(){}
    public:
        void setWings(int w);
        int getWings();

        void setWheels(int w);
        int getWheels();

        void setEngines(int e);
        int getEngines();
    public:
        virtual void fly();
    private:
        int wings;
        int wheels;
        int engines;
};


}//namespace avdance

#endif // __AIRPLANE_H__


