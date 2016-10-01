#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>

#include "ics3/ics"

int main(int argc, char **argv) {
  {
    std::cout << std::endl << "EepParam test section" << std::endl;
    ics::EepParam speed = ics::EepParam::speed();
    assert(127 == speed.get());
    speed.set(100);
    assert(100 == speed.get());
    try {
      speed.set(200);
      std::cerr << "Never run this" << std::endl;
    } catch (std::invalid_argument e) {
      std::cout << e.what() << std::endl;
    }
  }
  {
    std::cout << std::endl << "angle test section" << std::endl;
    ics::Angle degree = ics::Angle::createDegree();
    ics::Angle radian = ics::Angle::createRadian();
    assert(degree.getRaw() == radian.getRaw());
    degree.set(0);
    radian.set(0);
    assert(degree.getRaw() == radian.getRaw());
    degree.set(90);
    radian.set(M_PI / 2);
    assert(degree.getRaw() == radian.getRaw());
    degree.set(60);
    radian.set(M_PI / 3);
    assert(degree.getRaw() == radian.getRaw());
    try {
      degree.set(150);
      std::cerr << "Never run this" << std::endl;
    } catch (const std::invalid_argument &e) {
      std::cout << e.what() << std::endl;
    }
    try {
      radian.set(M_PI);
      std::cerr << "Never run this" << std::endl;
    } catch (const std::invalid_argument &e) {
      std::cout << e.what() << std::endl;
    }
  }
  {
    std::cout << std::endl << "parameter test section" << std::endl;
    ics::Parameter current = ics::Parameter::current();
    assert(63 == current.get());
    current.set(30);
    assert(30 == current.get());
    try {
      current.set(70);
      std::cerr << "Never run this" << std::endl;
    } catch (const std::invalid_argument &e) {
      std::cout << e.what() << std::endl;
    }
  }
  return 0;
}
