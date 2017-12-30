#include <sstream>
#include <iterator>
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <memory>
#include <numeric>
using namespace std;

// Given, should not be changed
struct Image_Data
{
    Image_Data(string const & line)
    {
        istringstream iss{line};
        iss >> type;
        for ( int d; iss >> d; )
        {
            args.push_back(d);
        }
    }
    string type;
    vector<int> args;
};

// Add your classes here
class Image {
public:
  Image(int w, int h)
    :w{w},h{h}
  {}
  virtual int size() = 0;
protected:
  int w;
  int h;
};

class PNG : public Image {
public:
  PNG(int w, int h)
    :Image{w,h}
  {}
  int size() override {
    return w*h*1.5;
  }
  static PNG* parse(Image_Data const& imgd) {
    if (imgd.type == "PNG") {
      return new PNG{imgd.args.at(0),imgd.args.at(1)};
    } else {
      return nullptr;
    }
  }
};

class BMP : public Image {
public:
  BMP(int w, int h)
    :Image{w,h}
  {}
  int size() override {
    return w*h*3;
  }

  static BMP* parse(Image_Data const& imgd) {
    if (imgd.type == "BMP") {
      return new BMP{imgd.args.at(0),imgd.args.at(1)};
    } else {
      return nullptr;
    }
  }
};

class JPG : public Image {
public:
  JPG(int w, int h, int q)
    :Image{w,h},q{q}
  {}
  int size() override {
    return w*h*3*(q/100.0);
  }
  static JPG* parse(Image_Data const& imgd) {
    if (imgd.type == "JPG") {
      return new JPG{imgd.args.at(0),imgd.args.at(1),imgd.args.at(2)};
    } else {
      return nullptr;
    }
  }

private:
  int q;
};
/*
 * Given code. No modifications allowed unless specified!
 */
Image* error_printer(Image_Data const & d)
{
    cout << "!!! " << d.type << " is an invalid file format !!!\n";
    return nullptr;
}
int main()
{
    vector<unique_ptr<Image>> images;
    vector<function<Image*(Image_Data const &)>> funs { PNG::parse,
                                                        JPG::parse,
                                                        BMP::parse,
                                                        error_printer};
    cout << "Enter one line for each image on the format \"type [type specific data]\". Exit with \"q\".\n\n";

    for ( string line; getline(cin, line); )
    {
        if ( line == "q" )
        {
            break;
        }
        Image_Data data{line};
        for ( auto && f: funs )
        {
            if (auto ptr = f(data))
            {
                images.emplace_back(ptr);
                break;
            }
        }
    }

// Additions allowed below (calculate and print sum)
    int sum = std::accumulate(begin(images),end(images), 0,
                              [](int const& current_sum,auto const& b) {
                                return current_sum + b->size();
                              });
    cout << "Total size: " << sum << " bytes!" << endl;
}
