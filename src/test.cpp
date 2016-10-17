#include<iostream>
#define _USE_MATH_DEFINES
#include<cmath>
#include<cassert>
#include<thread>
#include<chrono>

#include "ics3/ics"

int main(int argc, char **argv) {
  {
    std::cout << std::endl << "ID test section" << std::endl;
    ics::ID id {0};
    assert(id == 0);
    assert(id == 0);
    ics::ID id31 {31};
    assert(id31 == 31);
    assert(id31.get() == 31);
    try {
      ics::ID id32 {32};
      assert(false);
    } catch (std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }
  }
  {
    std::cout << std::endl << "EepParam test section" << std::endl;
    ics::EepParam speed = ics::EepParam::speed();
    assert(127 == speed.get());
    speed.set(100);
    assert(100 == speed.get());
    try {
      speed.set(200);
      std::cerr << "Never run this" << std::endl;
    } catch (std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }
  }
  {
    std::cout << std::endl << "angle test section" << std::endl;
    ics::Angle degree = ics::Angle::newDegree();
    ics::Angle radian = ics::Angle::newRadian();
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
    } catch (const std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }
    try {
      radian.set(M_PI);
      std::cerr << "Never run this" << std::endl;
    } catch (const std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }
  }
  {
    std::cout << std::endl << "angle factory test section" << std::endl;
    ics::Angle degree = ics::Angle::newDegree(90);
    ics::Angle radian = ics::Angle::newRadian(M_PI / 2);
    assert(degree.getRaw() == radian.getRaw());
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
    } catch (const std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }
  }
  {
    std::cout << std::endl << "ICS3 test section" << std::endl;
    ics::ID id(2);
    ics::Angle degree = ics::Angle::newDegree();
    try {
      ics::ICS3 ics("/dev/ttyUSB0");
      assert(7500 == degree.getRaw());
      ics::Angle nowPos = ics.move(id, degree);
      std::cout << nowPos.get() << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      degree.set(50);
      nowPos = ics.move(id, degree);
      std::cout << nowPos.get() << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      degree.set(-50);
      nowPos = ics.move(id, degree);
      std::cout << nowPos.get() << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      degree.set(0);
      nowPos = ics.move(id, degree);
      std::cout << nowPos.get() << std::endl;
      nowPos = ics.free(id);
      std::cout << nowPos.get() << std::endl;
    } catch (std::runtime_error& e) {
      std::cout << e.what() << std::endl;
    }
  }
  return 0;
}
