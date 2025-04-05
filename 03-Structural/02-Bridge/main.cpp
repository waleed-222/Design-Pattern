#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Color{
public:
    virtual ~Color()=default;
    virtual std::string applyColor()const=0;
};

class BlueColor : public Color{
public:
std::string applyColor()const override{return "Blue";}
};


class RedColor : public Color{
    public:
    std::string applyColor()const override{return "Red";}
};

class Shape{
protected:
    std::shared_ptr<Color> color;
public:
    Shape(std::shared_ptr<Color>color):color(std::move(color)){}
    virtual ~Shape()=default;
    virtual void draw() const=0;   
};

class Circle : public Shape{
    public:
    Circle( std::shared_ptr<Color>color):Shape(std::move(color)){}
    void draw()const override{std::cout<<"Drawing a "<<color->applyColor()<<" Circle\n";}

};

class Square : public Shape{
    public:
    Square( std::shared_ptr<Color>color):Shape(std::move(color)){}
    void draw()const override{std::cout<<"Drawing a "<<color->applyColor()<<" Square\n";}
    
};

int main(){
    auto red=std::make_shared<RedColor>();
    auto blue=std::make_shared<BlueColor>();
    Circle redCircle(red);
    Square blueSquare(blue);
    redCircle.draw();
    blueSquare.draw();
    return 0;
}