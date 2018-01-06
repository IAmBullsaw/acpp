#include <iostream>
#include <string>
#include <vector>
// Abstract slab
class Slab{
public:
  Slab(Slab const&) = delete;
  Slab& operator=(Slab const&) = delete;

  virtual ~Slab() = default;

  std::string get_color() const {return color_;}
  double get_weight() const {return weight_;}
  std::string get_size() const {return size_;}
  virtual Slab* clone() const = 0;

  Slab(std::string const& color, double const& weight, std::string const& size)
    :color_{color}, weight_{weight}, size_{size}
  {}

private:
  std::string const color_;
  double const weight_;
  std::string const size_;
};

class Concrete : public Slab {
public:
  Concrete(std::string const& color, double const& weight, std::string const& size, bool const& tumbled = false)
    :Slab{color,weight,size},tumbled_{tumbled}
  {}
  bool tumbled() const {return tumbled_;}

  Slab* clone() const override {
    return new Concrete{get_color(),get_weight(),get_size(),tumbled_};
  }

private:
  bool const tumbled_;
};

class Rock : public Slab {
public:
  Rock(double const& weight, std::string const& size, std::string const& type)
    :Slab{"Nature",weight,size},type_{type}
  {}
  std::string get_type() const {return type_;}
  Slab* clone() const override {
    return new Rock{get_weight(),get_size(),type_};
  }

private:
  std::string const type_;
};

class Brick: public Slab {
public:
  using Slab::Slab;
  Slab* clone() const override {
    return new Brick{get_color(),get_weight(),get_size()};
  }
};

void test(Slab const & s)
{
  // Create a copy of the object that s refers to
  //
  auto copy = s.clone();
  // Print the information about the copy. With objects constructed according to the
  // comments in main, the printout should be:
  // Concrete: Gray, 25x12x4, 2.8kg
  // Rock: Granite, Nature, 12x15x10, 10.5kg
  // Brick: Red, 25x10x10, 3.2kg
  // Concrete: Graphite, 20x20x6, 3.9kg, tumbled
  //
  bool tumbled{false};
  if (auto p = dynamic_cast<Concrete const*>(copy)) {
    tumbled = p->tumbled();
    std::cout << "Concrete: ";
  } else if (auto p =dynamic_cast<Rock const*>(copy)) {
    std::cout << "Rock: " << p->get_type() << " ";
  } else {
    std::cout << "Brick: ";
  }
  std::cout << copy->get_color() << ", "
            << copy->get_size() << ", "
            << copy->get_weight() << "kg"
            << (tumbled ? ", tumbled\n" : "\n") ;
  // Destroy the copy
  delete copy;
  copy = nullptr;
}

int main()
{
  // Create the following objects dynamically and store in some kind of container:
  // Type      Color    Size      Weight   type/tumbled
  // --------------------------------------------------
  // Concrete  Gray     25x12x4   2.8
  // Rock               12x15x10  10.5     Granite
  // Brick     Red      25x10x10  3.2
  // Concrete  Graphite 20x20x6   3.9      true

  std::vector<Slab const*> slabs{
    new Concrete{"Gray", 2.8, "25x12x4"},
      new Rock{10.5, "25x12x4", "Granite"},
        new Brick{"Red", 3.2, "25x10x10"},
          new Concrete{"Graphite", 3.9, "20x20x6", true}
  };

  for (auto & slab : slabs) {
    test(*slab);
    delete slab;
    slab = nullptr;
  }

  // pass each object to test.

  return 0;
}
