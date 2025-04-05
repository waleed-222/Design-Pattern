#include <iostream>
#include<memory>

class Shape{
public:
    virtual ~Shape() = default;

    virtual std::unique_ptr<Shape> clone()const=0;
    virtual void draw()const=0;
};

class Circle :public Shape{
public:
Circle(const std::string& color, int size):color(color),size(size){}
std::unique_ptr<Shape> clone()const override{
return std::make_unique<Circle>(*this);
}
void draw()const override{
std::cout<<"Drawing a "<<color<<" Circle of size:"<<size << std::endl;
}



private:
std::string color;
int size;
};

class Square :public Shape{
    public:
        Square(const std::string& color, int size):color(color),size(size){}
        std::unique_ptr<Shape> clone()const override{
        return std::make_unique<Square>(*this);
        }
        void draw()const override{
        std::cout << "Drawing a "<<color<<" Square of size:"<<size << std::endl;
        }
    
    private:
        std::string color;
        int size;
};

int main(){
    Circle prototypeCircle ("Red",10);
    Square prototypeSquare ("Yellow",15);

    auto Circle1=prototypeCircle.clone();
    auto Circle2=prototypeCircle.clone();
    auto square1=prototypeSquare.clone();

    Circle1->draw();
    Circle2->draw();
    square1->draw();
    return 0;
}
