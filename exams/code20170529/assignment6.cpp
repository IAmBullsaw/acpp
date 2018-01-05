#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// abstracts
class Fruit {
public:
  Fruit(int const& mass)
    :mass_{mass}
  {}
  virtual ~Fruit() = default;

  virtual string name() const = 0;
  virtual bool dehiscant() const {return false;}
  virtual int mass() const {return mass_;}

  int vitamin_c_content() {
    return mass_ * concentration() / 100.0;
  }

protected:
  virtual double concentration() const  = 0; // expressed in mg/100g

private:
  int mass_; // expressed in gram
};

class Berry : public Fruit {
public:
  Berry(int const& mass)
    :Fruit(mass)
  {}
};

// Instances

class Lemon : public Berry {
public:
  using Berry::Berry;
  string name() const override { return "Lemon";}
  double concentration() const  override { return 53;}
};

class Apple : public Fruit {
public:
  Apple(int const& mass)
    :Fruit(mass)
  {}

  string name() const override { return "Apple";}
  double concentration() const override { return 4.6;}
};

class Pea : public Fruit {
public:
  Pea(int const& mass)
    :Fruit(mass)
  {}

  string name() const override { return "Pea";}
  double concentration() const  override { return 40;}
  bool dehiscant() const  override {return true;}
};

void print(Fruit const & f)
{
  // Print Berry if f is a berry or Fruit otherwise

  cout << f.name() << " with mass " << f.mass() << "g [";
  if ( !f.dehiscant() )
    {
      cout << "in";
    }
  cout << "dehiscant]\n";

}

int main()
{
  // create a vector containing the following fruits:
  //  Apple, mass: 150g
  //  Lemon, mass: 75g
  //  Pea, mass: 25g
  //
  vector<Fruit*> fruits {
    new Apple{150},
      new Lemon{75},
        new Pea{25}
  };
  // Iterate through the vector and pass each fruit to print above, should give the following output
  // Fruit, Apple with mass 150g [indehiscant]
  // Berry, Lemon with mass 75g [indehiscant]
  // Fruit, Pea with mass 25g [dehiscant]
  int total_content {};
  for_each(begin(fruits),end(fruits),
           [&total_content](auto fruit){
             print(*fruit);
             total_content += fruit->vitamin_c_content();

             // We done with fruit
             delete fruit;
             fruit = nullptr;
           });
  // Calculate the total vitamin C content of all fruit

  cout << "Total vitamin C content: " << total_content << endl;
}
