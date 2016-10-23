#include<iostream>
#include<cassert>
#include<thread>
#include<chrono>

#include "ics3/ics"

void testAngle();
void testBaudrate();
void testEepParam();
void testID();
void testParameter();
void testICS3();

template<typename Iter> constexpr void dump(Iter&& begin, Iter&& end) noexcept;

int main() {
  testAngle();
  testBaudrate();
  testEepParam();
  testID();
  testParameter();
  testICS3();
  return 0;
}

void testAngle() {
  std::cout << std::endl << "angle test section" << std::endl;
  // constexpr test
  constexpr auto defDeg = ics::Angle::newDegree();
  constexpr auto defRad = ics::Angle::newRadian();
  static_assert(defDeg == 0, "Angle default cast error");
  static_assert(defRad.get() == 0, "Angle default get() error");
  static_assert(defDeg.getRaw() == 7500, "Angle default must is 7500");
  static_assert(defDeg.getRaw() == defRad.getRaw(), "Angle have different default");
  constexpr auto degree1 = ics::Angle::newDegree(90);
  constexpr auto radian1 = ics::Angle::newRadian(M_PI / 2);
  static_assert(degree1.getRaw() == radian1.getRaw(), "difference: 90 deg <-> pi/2 rad");
  constexpr auto degree2 = ics::Angle::newDegree(30);
  constexpr auto radian2 = ics::Angle::newRadian(M_PI / 6);
  static_assert(degree2.getRaw() == radian2.getRaw(), "difference: 30 deg <-> pi/6 rad");
  try {
    ics::Angle::newDegree(136);
    assert(false);
  } catch (std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
  }

  // runtime test
  auto degree = ics::Angle::newDegree(0);
  auto radian = ics::Angle::newRadian(0);
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
  } catch (std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    radian.set(M_PI);
    assert(false);
  } catch (std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
  }
}

void testBaudrate() {
  std::cout << std::endl << "Baudrate test section" << std::endl;
  // constexpr test
  constexpr auto baudrate115200 = ics::Baudrate::RATE115200();
  static_assert(baudrate115200 == B115200, "Baudrate: not equal B115200");
  static_assert(baudrate115200.getRomData() == 10, "Baudrate: romdata error");
  static_assert(baudrate115200.get() == B115200, "Baudrate: get method error");
}

void testEepParam() {
  std::cout << std::endl << "EepParam test section" << std::endl;
  // constexpr test
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

  // runtime test
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

void testID() {
  std::cout << std::endl << "ID test section" << std::endl;
  constexpr ics::ID id {0};
  static_assert(id == 0, "id 0 error");
  static_assert(id.get() == 0, "id 0 error by get");
  constexpr ics::ID id31 {31};
  static_assert(id31 == 31, "id 31 error");
  static_assert(id31.get() == 31, "id 31 error by get");
  try {
    ics::ID id32 {32}; // if constexpr, compile error
    assert(false);
  } catch (std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    ics::ID error {static_cast<unsigned char>(-1)}; // if constexpr, compile error
    assert(false);
  } catch (std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
  }
}

void testParameter() {
  std::cout << std::endl << "parameter test section" << std::endl;
  // constexpr test
  constexpr auto stretch = ics::Parameter::stretch();
  static_assert(30 == stretch.get(), "stretch error");
  static_assert(30 == stretch, "stretch error by cast");
  static_assert(0x01 == stretch.getSubcommand(), "stretch error by subcommand");
  constexpr auto speed = ics::Parameter::speed(100);
  static_assert(100 == speed.get(), "speed error");
  static_assert(100 == speed, "speed error by cast");
  static_assert(0x02 == speed.getSubcommand(), "speed error by subcommand");
  try {
    ics::Parameter::temperature(0);
    assert(false);
  } catch (std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
  }

  // runtime test
  auto current = ics::Parameter::current();
  assert(63 == current.get());
  assert(0x03 == current.getSubcommand());
  current.set(30);
  assert(30 == current);
  current = 10;
  assert(10 == current);
  try {
    current.set(70);
    assert(false);
  } catch (std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    current = 64;
    assert(false);
  } catch (std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
  }
}

void testICS3() {
  std::cout << std::endl << "ICS3 test section" << std::endl;
  constexpr auto baudrate = ics::Baudrate::RATE115200();
  constexpr ics::ID id {2};
  auto degree = ics::Angle::newDegree();
  try {
    ics::ICS3 ics {"/dev/ttyUSB0", baudrate};
    std::cout << "move to " << degree << " [deg]" << std::endl;
    auto nowPos = ics.move(id, degree);
    std::cout << "now pos is " << nowPos << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    degree = 50;
    std::cout << "move to " << degree << " [deg]" << std::endl;
    nowPos = ics.move(id, degree);
    std::cout << "now pos is " << nowPos << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    degree = -50;
    std::cout << "move to " << degree << " [deg]" << std::endl;
    nowPos = ics.move(id, degree);
    std::cout << "now pos is " << nowPos << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    degree = 0;
    std::cout << "move to " << degree << " [deg]" << std::endl;
    nowPos = ics.move(id, degree);
    std::cout << "now pos is " << nowPos << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    std::cout << "free torque" << std::endl;
    nowPos = ics.free(id);
    std::cout << "now pos is " << nowPos << std::endl;
  } catch (std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
}

template<typename Iter> constexpr void dump(Iter&& begin, Iter&& end) noexcept {
  while (begin != end) std::cout << *begin << ", ";
  std::cout << std::endl;
}
