/**
 *for testing class and use it
 */

#include<iostream>
#include "Human.h"

using namespace std;
int main(int argc,char* argv[]){
//    Human human;//在栈中分配空间
    Human * human =new Human(); //在堆中分配空间
    human->setAge(18);
    human->setSex(0);
    cout<<"human:"<<human->getAge()<<", "<<human->getSex()<<endl;

    delete human;

    return 0;
}
