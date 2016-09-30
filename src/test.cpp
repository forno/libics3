#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

#include "ics3/ics"

int main(int argc, char **argv) {
  std::cout << "angle of degree test section" << std::endl;
  {
    ics::Angle degree = ics::Angle::createDegree();
    degree.set(0);
    std::cout << degree.get() << ':' << degree.getRaw() << std::endl;
    degree.set(90);
    std::cout << degree.get() << ':' << degree.getRaw() << std::endl;
    degree.set(60);
    std::cout << degree.get() << ':' << degree.getRaw() << std::endl;
  }
  {
    std::cout << "angle of radian test section" << std::endl;
    ics::Angle radian = ics::Angle::createRadian();
    radian.set(0);
    std::cout << radian.get() << ':' << radian.getRaw() << std::endl;
    radian.set(M_PI / 2);
    std::cout << radian.get() << ':' << radian.getRaw() << std::endl;
    radian.set(M_PI / 3);
    std::cout << radian.get() << ':' << radian.getRaw() << std::endl;
  }
  {
    std::cout << "parameter test section" << std::endl;
    ics::Parameter current = ics::Parameter::current();
    current.set(30);
    std::cout << static_cast<int>(current.get()) << std::endl;
  }
  return 0;
}
