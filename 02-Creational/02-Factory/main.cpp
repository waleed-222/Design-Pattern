#include <iostream>
#include <memory>

class Button{
public:
    virtual void render() const=0;
    virtual ~Button()=default;
};

class WindowsButton : public Button{
public:
void render() const override{
    std::cout<<"Rendering Windows Button"<<std::endl;
}
};

class MacOSButton : public Button{
public:
void render()const override{
    std::cout<<"Rendering MacOS Button"<<std::endl;
}
};

class Dialog{
public:
virtual std::unique_ptr<Button> createButton() const=0;
void render()const{
    auto button=createButton();
    button->render();
}
virtual ~Dialog()=default;
};

class WindowDialog : public Dialog{
public:
std::unique_ptr<Button> createButton() const override{
    return  std::make_unique<WindowsButton>();
}
};

class MacOSDialog : public Dialog{
    public:
    std::unique_ptr<Button> createButton() const override{
        return  std::make_unique<MacOSButton>();
    }
    };

int main(){

    std::unique_ptr<Dialog> dialog =std::make_unique<WindowDialog>();
    dialog->render();
    dialog=std::make_unique<MacOSDialog>();
    dialog->render();

    return 0;

}

