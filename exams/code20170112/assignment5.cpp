#include <iostream>
#include <string>
using namespace std;

// Abstract class
class Game {
public:

  string name() const {
    return m_name;
  }

  void print(ostream& os) const  {
    os << "<Game " << m_name << ">\n";
  }

  void usingStuff() {
    cout << m_min_players * m_max_players;
  }

protected:
  Game(string const& name, int const& min, int const& max)
    :m_name{name}, m_min_players{min}, m_max_players{max}
  {}

private:
  string m_name;
  int m_min_players;
  int m_max_players;
};


class Board_Game: public Game {
public:
  Board_Game(string const& name, int const& min, int const& max,int const& width, int const& height)
    :Game(name, min, max), width{width}, height{height} {}

  string size() const {
    return to_string(width) + "x" + to_string(height) + "cm";
  }

private:
  int width;
  int height;
};

class Cooperative: public Board_Game {
public:
  Cooperative(string const& name, int const& min, int const& max,int const& width, int const& height, bool const& traitor = false)
    :Board_Game(name, min, max, width, height), m_traitor{traitor} {}

  void usingStuff() {
    cout << m_traitor;
  }

private:
  bool m_traitor;
};

class Card_Game: public Game {
public:
  Card_Game(string const& name, int const& min, int const& max, bool const& standard_deck = true)
    :Game(name, min, max), m_standard_deck{standard_deck} {}
private:
  void usingStuff() {
    cout << m_standard_deck;
  }

  bool m_standard_deck;
};

int main() {
  // Game a("shouldn't work",1,2);



  return 0;
}
