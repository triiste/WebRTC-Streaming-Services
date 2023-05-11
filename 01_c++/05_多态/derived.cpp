#include<iostream>
#include "FighterPlane.h"
#include "AirPlane.h"
#include "NonePlane.h"

int main(int argc,char * argv[]){
    avdance::AirPlane *ap = new avdance::FighterPlane();
    if(ap){
        ap->fly();
    }
    avdance::AirPlane *np = new avdance::NonePlane();
    if(np){
        np->fly();
    }
    ap =new avdance::AirPlane();
    if(ap){
        ap->fly();    
    }
    



/*    fp.setWings(5);
    fp.setWheels(3);
    fp.setWeapons(10);

    std::cout<<"FighterPlane:"<<fp.getWings()<<","
                              <<fp.getWheels()<<","
                              <<fp.getWeapons()<<std::endl;
*/
}


