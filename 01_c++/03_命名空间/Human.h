#ifndef __HUMAN_H__ //防止重复引入
#define __HUMAN_H__ //防止重复引入
#include<iostream>
namespace avdance {

using namespace std;
class Human{
    public:
        Human(){
            cout<<"construct human .. " <<endl;
            age = 0;
            sex = 0;
        }
        ~Human(){
            cout<<"destruct human..."<<endl;
        }
    public:
        void setAge(int a);
        int getAge();
        void setSex(int s);
        int getSex();
    private:
        int age;//年龄       
        int sex;//性别 0：male 1:female

};
 
}//namespace

#endif //__HUMAN_H__

