#include<iostream>
#include<cassert>
#include<thread>
#include<chrono>

#include "ics3/ics"

int main(int argc, char **argv) {
  {
    std::cout << std::endl << "ID test section" << std::endl;
    constexpr ics::ID id {0};
    static_assert(id == 0, "id 0 error");
    static_assert(id.get() == 0, "id 0 error by get");
    constexpr ics::ID id31 {31};
    static_assert(id31 == 31, "id 31 error");
    static_assert(id31.get() == 31, "id 31 error by get");
    try {
      ics::ID id32 {32}; // if constexpr, compile error.
      assert(false);
    } catch (std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }
    try {
      ics::ID error {static_cast<unsigned char>(-1)}; // if constexpr, compile error.
      assert(false);
    } catch (std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }
  }
  {
    std::cout << std::endl << "EepParam test section" << std::endl;
    constexpr auto current = ics::EepParam::current();
    static_assert(63 == current.get(), "current error");
    constexpr auto strech = ics::EepParam::strech(244);
    static_assert(244 == strech.get(), "strech error");
    try {
      ics::EepParam::flag(10);
      assert(false);
    } catch (std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }

    auto speed = ics::EepParam::speed();
    assert(127 == speed.get());
    speed.set(100);
    assert(100 == speed.get());
    try {
      speed.set(200);
      assert(false);
    } catch (std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }
  }
  {
    std::cout << std::endl << "angle test section" << std::endl;
    constexpr auto degree1 = ics::Angle::newDegree(90);
    constexpr auto radian1 = ics::Angle::newRadian(M_PI / 2);
    static_assert(degree1.getRaw() == radian1.getRaw(), "angles 1 error");
    constexpr auto degree2 = ics::Angle::newDegree(30);
    constexpr auto radian2 = ics::Angle::newRadian(M_PI / 6);
    static_assert(degree2.getRaw() == radian2.getRaw(), "angles 2 error");
    try {
      ics::Angle::newDegree(136);
      assert(false);
    } catch (std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }

    auto degree = ics::Angle::newDegree();
    auto radian = ics::Angle::newRadian();
    assert(degree.getRaw() == radian.getRaw());
    degree.set(0);
    radian.set(0);
    assert(degree.getRaw() == radian.getRaw());
    degree.set(90);
    radian.set(M_PI / 2);
    assert(degree.getRaw() == radian.getRaw());
    degree.set(-60);
    radian.set(-M_PI / 3);
    assert(degree.getRaw() == radian.getRaw());
    try {
      degree.set(150);
      assert(false);
    } catch (const std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }
    try {
      radian.set(M_PI);
      assert(false);
    } catch (const std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }
  }
  {
    std::cout << std::endl << "parameter test section" << std::endl;
    auto current = ics::Parameter::current();
    assert(63 == current.get());
    current.set(30);
    assert(30 == current.get());
    try {
      current.set(70);
      assert(false);
    } catch (const std::invalid_argument& e) {
      std::cout << e.what() << std::endl;
    }
  }
  {
    std::cout << std::endl << "ICS3 test section" << std::endl;
    auto id(2);
    auto degree = ics::Angle::newDegree();
    try {
      ics::ICS3 ics {"/dev/ttyUSB0"};
      assert(7500 == degree.getRaw());
      auto nowPos = ics.move(id, degree);
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
