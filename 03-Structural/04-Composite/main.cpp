#include <iostream>
#include <memory>
#include <vector>

class Item {
public:
  virtual ~Item() = default;
  virtual double getPrice() const = 0;
  virtual void printDetails(const std::string& indent="") const = 0;
};

class Product : public Item {
public:
  Product(const std::string &name,double price) : price(price), name(name) {}

  double getPrice() const override { return price; }

  void printDetails(const std::string& indent="") const override {
    std::cout<<indent<<" Product: "<<name<<" ,Price: "<<price<<std::endl;
  }

private:
  double price;
  std::string name;
};

class Box : public Item {
public:
  void addItem(const std::shared_ptr<Item> &item) {
    items.push_back(item);
  }

  double getPrice() const override { 
    double total=0;
    for(const auto& item :items){
      total+=item->getPrice();
    }
    return total; }

  void printDetails(const std::string& indent="") const override {
    std::cout<<indent <<" Box Contains:\n";
    for(const auto& item:items){
      item->printDetails(indent +" ");
    }
  }

private:
  std::vector<std::shared_ptr<Item>> items;
};


int main(){
  auto phone=std::make_shared<Product>("SmartPhone",666.99);
  auto laptop =std::make_shared<Product>("Laptop",999.99);
  auto headphone =std::make_shared<Product>("Headphone",199.99);

  auto smallBox=std::make_shared<Box>();
  smallBox->addItem(phone);
  smallBox->addItem(headphone);

  auto bigBox =std::make_shared<Box>();
  bigBox->addItem(laptop);
  bigBox->addItem(smallBox);

  bigBox->printDetails();
  std::cout<<"Total Price:"<<bigBox->getPrice()<<"$\n";

  return 0;
}