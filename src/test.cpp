#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

#include "ics3/ics"

int main(int argc, char **argv) {
  std::cout << "angle of degree test section" << std::endl;
  {
    ics::Angle degree = ics::Angle::createDegree();
    std::cout << degree.get() << ':' << degree.getRaw() << std::endl;
    degree.set(0);
    std::cout << degree.get() << ':' << degree.getRaw() << std::endl;
    degree.set(90);
    std::cout << degree.get() << ':' << degree.getRaw() << std::endl;
    degree.set(60);
    std::cout << degree.get() << ':' << degree.getRaw() << std::endl;
    try {
      degree.set(150);
      std::cerr << "Never run this" << std::endl;
    } catch (const std::invalid_argument &e) {
      std::cout << e.what() << std::endl;
    }
  }
  {
    std::cout << std::endl << "angle of radian test section" << std::endl;
    ics::Angle radian = ics::Angle::createRadian();
    std::cout << radian.get() << ':' << radian.getRaw() << std::endl;
    radian.set(0);
    std::cout << radian.get() << ':' << radian.getRaw() << std::endl;
    radian.set(M_PI / 2);
    std::cout << radian.get() << ':' << radian.getRaw() << std::endl;
    radian.set(M_PI / 3);
    std::cout << radian.get() << ':' << radian.getRaw() << std::endl;
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
    std::cout << static_cast<int>(current.get()) << std::endl;
    current.set(30);
    std::cout << static_cast<int>(current.get()) << std::endl;
    try {
      current.set(70);
      std::cerr << "Never run this" << std::endl;
    } catch (const std::invalid_argument &e) {
      std::cout << e.what() << std::endl;
    }
  }
  {
    std::cout << std::endl << "EepParam test section" << std::endl;
    ics::EepParam speed = ics::EepParam::speed();
    std::cout << speed.get() << std::endl;
    speed.set(100);
    std::cout << speed.get() << std::endl;
    try {
      speed.set(200);
      std::cerr << "Never run this" << std::endl;
    } catch (std::invalid_argument e) {
      std::cout << e.what() << std::endl;
    }
  }
  return 0;
}
