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

int main(int argc, char **argv) {
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
  static_assert(defDeg == 0, "Angle default deg error");
  static_assert(defRad.get() == 0, "Angle default rad error");
  static_assert(defDeg.getRaw() == defRad.getRaw(), "Error: Angle have different default");
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
  constexpr struct {
    static constexpr speed_t speed(speed_t baudrate, speed_t value) {
      return baudrate != value ? throw std::invalid_argument {"Baudrate: speed error"} : baudrate;
    }
    static constexpr uint16_t romdata(uint16_t baudrate, uint16_t value) {
      return baudrate != value ? throw std::invalid_argument {"Baudrate: romdata error"} : baudrate;
    }
  } checker;
  checker.speed(baudrate115200, B115200);
  checker.romdata(baudrate115200, 10);
  static_assert(static_cast<uint16_t>(baudrate115200) == 10, "Baudrate: not equal 10");
  static_assert(static_cast<speed_t>(baudrate115200) == B115200, "Baudrate: not equal B115200");
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
