#include <iostream>
#include <memory>
#include <utility>


class Serverinterface{
public:
    virtual ~Serverinterface()=default;
    virtual void operation() const =0;
};

class Service: public Serverinterface{
public:
void operation() const override{
    std::cout<<"Service: handling the operation\n ";
}
};

class Proxy : public Serverinterface{
private:
    std::shared_ptr<Service>service;
    bool checkAccess()const{
        std::cout<<"Proxy: Checking Access....\n";
        return true;
    }
public:
    Proxy(std::shared_ptr<Service>realService):service(std::move(realService)){}

    void operation() const override{
        if(checkAccess()){
            std::cout<<"Proxy: Accaess granted. Forwarding request to the real service\n ";
            service->operation();
        }
        else
        {
        std::cout<<"Proxy: Access Denaied\n";
        }
    }

};
void clientCode(const Serverinterface & service ){service.operation();}

int main(){
    auto realService=std::make_shared<Service>();
    Proxy proxy(realService);
    std::cout<<"Client: Executing the operation through the proxy\n";
    clientCode(proxy);

    return 0;
}