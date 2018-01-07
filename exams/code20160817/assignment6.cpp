/*
 * program6.cc
 */
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Define Celestial_Body classes here

class Celestial_Body {
public:
  Celestial_Body(string const& name, double const& size)
    :name_{name},size_{size}
  {}

  virtual ~Celestial_Body() = 0;

  string get_name() const { return name_;}
  double get_size() const { return size_;}

  Celestial_Body(Celestial_Body const&) = delete; // Copy constructor
  Celestial_Body& operator=(Celestial_Body const&) = delete; // Copy assignment

private:
  string const name_;
  double const size_;
};
Celestial_Body::~Celestial_Body() = default;

class Star : public Celestial_Body {
public:
  Star(string const& name, double const& size, string const& galaxy)
    :Celestial_Body{name,size},galaxy_{galaxy}
  {}

  string get_galaxy() const {return galaxy_;}
private:
  string const galaxy_;
};

class Planet : public Celestial_Body {
public:
  Planet(string const& name, double const& size,
       Celestial_Body const& celestial_body, double const& orbit_time, bool const& populated = false)
    :Celestial_Body(name,size),celestial_body_{celestial_body},orbit_time_{orbit_time},populated_{populated}
  {}

  auto get_celestial_body() const {return &celestial_body_;}
  auto get_orbit_time() const {return orbit_time_;}
  auto is_populated() const {return populated_;}
  auto populated(bool const& populated ) {populated_ = populated;}

private:
  Celestial_Body const& celestial_body_;
  double const orbit_time_;
  bool populated_;
};

class Moon : public Planet {
public:
  Moon(string const& name, double const& size,
         Planet const& celestial_body, double const& orbit_time, bool const& populated = false)
    :Planet(name,size,celestial_body,orbit_time,populated)
  {}
};

void print(const Celestial_Body& cb)
{
  // Depending on kind of celestial body, print its correspending data. Output
  // shall be as follows:
  auto p{dynamic_cast<Planet const*>(&cb)};
  auto s{dynamic_cast<Star const*>(&cb)};
  auto m{dynamic_cast<Moon const*>(&cb)};

  cout << cb.get_name() << ": ";

  if (m) {
    cout << "moon, ";
  } else if (s) {
    cout << "star, ";
  } else if (p) {
    cout << "planet, ";
  }

  cout << fixed << setprecision(1) << cb.get_size() << " km, belongs to ";


  if (s) {
    cout << "galaxy, " << s->get_galaxy();
  } else if (p) {
    cout << (m ? "planet, " : "star, ")
         << p->get_celestial_body()->get_name()
         << ", orbit time "
         << p->get_orbit_time() << " days, "
         << (p->is_populated() ? "populated":"not populated");
  }
  cout << "\n";

  // Helios: star, radius 696342.0 km, belongs to galaxy Milky Way
  // Earth: planet, radius 6371.0 km, belongs to star Helios, orbit time 365.2 days, populated
  // Moon: moon, radius 1737.1 km, belongs to planet Earth, orbit time 27.3 days, not populated
}

int main()
{
  // Declare statically one object of each of type Star, Planet, and Moon. Use
  // the following data to initialize the objects (use defaults when suitable):
  // Star: name Helios, radius 696342.0, belongs to galaxy Milky Way
  // Planet: name Earth, radius 6371.0, belongs to star Helios, orbit time 365.2 days, populated
  // Moon: name Moon, radius 1737.1, belongs to planet Earth, orbit time 27.3 days, not populated

  Star helios{"Helios", 696342.0, "Milky Way"};
  Planet erf{"Earth", 6371.0, helios, 365.2, true};
  Moon moooooooooooooooooooooooooooooooooooooooooon{"Moon", 1737.1, erf, 27.3};

  // Call print() for each object above.
  print(helios);
  print(erf);
  print(moooooooooooooooooooooooooooooooooooooooooon);
  return 0;
}
