#include <iostream>
#include <vector>

class Singleton{
public:
    static Singleton &get_instance(){
        static Singleton instance;
        return instance;
    }

    void showMessage()const{
        std::cout<<"Singleton Instance Address: "<<this<<std::endl;
    }

    void pushData(int data){database.push_back(data);}

    Singleton(const Singleton &)=delete;
    Singleton &operator=(const Singleton)=delete;

private:
    Singleton(){}
    std::vector<int> database;

};

int main(){
    Singleton &instance1=Singleton::get_instance();
    const Singleton &instance2=Singleton::get_instance();
    instance1.pushData(10);
    instance1.showMessage();
    instance2.showMessage();


    return 0;
}