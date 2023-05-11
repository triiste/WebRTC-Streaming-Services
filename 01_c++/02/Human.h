#include<iostream>
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
