#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Abstract class
class Game {
public:
  virtual string name() const {
    return m_name;
  }

  virtual void print(ostream& os) const  {
    os << type() << " \"" << name() << "\" has " + to_string(m_min_players) + " to " + to_string(m_max_players) + " players ";
  }

  virtual bool choose() const {
    cout << "How many players?: ";
    int response;
    cin >> response;
    return m_min_players <= response && response <= m_max_players;
  }

  // According to assignment!
  Game(Game const &) = delete;
  Game &operator=(Game const &) = delete;


protected:
  Game(string const& name, int const& min, int const& max)
    :m_name{name}, m_min_players{min}, m_max_players{max}
  {}
  virtual ~Game() = default;

  virtual string type() const {
    return "Game";
  }
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

  virtual void print(ostream& os) const override {
    Game::print(os);
    os << "with size " << size();
  }

  virtual bool choose() const override {
    if (!Game::choose()) return false;

    cout << "Do you have space for " << size() << "? [y/n]: ";
    char r;
    cin >> r;
    return r == 'y';
  }

protected:
  virtual string type() const override {
    return "Board " + Game::type();
  }

private:
  int width;
  int height;
};

class Cooperative: public Board_Game {
public:
  Cooperative(string const& name, int const& min, int const& max,int const& width, int const& height, bool const& traitor = false)
    :Board_Game(name, min, max, width, height), m_traitor{traitor} {}

  virtual bool choose() const override {
    if (!Board_Game::choose()) return false;

    cout << "Do you want a traitor? [y/n]: ";
    char r;
    cin >> r;
    return (r == 'y' && m_traitor) || (r != 'y' && !m_traitor) ;
  }

  virtual void print(ostream& os) const override {
    Board_Game::print(os);
    if (m_traitor) {
      os << "with a traitor ";
    }
  }

protected:
  virtual string type() const override {
    return "Cooperative " + Board_Game::type();
  }

private:
  bool m_traitor;
};

class Card_Game: public Game {
public:
  Card_Game(string const& name, int const& min, int const& max, bool const& standard_deck = true)
    :Game(name, min, max), m_standard_deck{standard_deck} {}

  virtual void print(ostream& os) const override {
    Game::print(os);
    os << "and you will " << (m_standard_deck ? "not " : " ") << "need a special deck of cards";
  }

protected:
  virtual string type() const override {
    return "Card " + Game::type();
  }

private:
  bool m_standard_deck;
};

// Given function
void select_game(vector<Game*> const & games)
{
  for ( Game const * g: games )
    {
      if ( g->choose() )
        {
          g->print(cout);
          cout << endl;
        }
    }
}

/*
  Here lies main,
  No dragons here.
*/
int main() {
  // Game a("shouldn't work",1,2); Instanciation of an abstract class?
  vector<Game*> games{
    new Board_Game("Monopoly",2,4,51,51),
      new Cooperative("Pandemic",2,5,41,57),
      new Cooperative("Battle Star Galactica",4,7,100,120,true),
      new Card_Game("Solitaire",1,1),
      new Card_Game("Bang!",3,7,true)};
  select_game(games);
  return 0;
}
