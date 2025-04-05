#include <iostream>

class OldSystem{
public:
    virtual void  OldOperation(){std::cout<<"Old system operation executed\n";}
    virtual ~OldSystem()=default;
};

class NewSystem{
public:
    void newOperation(){std::cout<<"New system operation executed\n";}
};

class Adapter :public OldSystem{
NewSystem * newsystem;
public:
Adapter(NewSystem * system):newsystem((system)){}
void OldOperation()override{
    newsystem->newOperation();
}
};

void execute(OldSystem* system){system->OldOperation();}

int main(){
    OldSystem *oldsystem=new Adapter(new(NewSystem));
    execute(oldsystem);
    delete oldsystem;
    return 0;
}