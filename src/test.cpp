#include "ics3/ics"

#include<iostream>
#include<cassert>
#include<thread>
#include<chrono>

void testAngle();
void testBaudrate();
void testEepParam();
void testID();
void testParameter();
void testICS3();
void testIcsMove(ics::ICS3&, const ics::ID&);
void testIcsParam(ics::ICS3&, const ics::ID&);
void testIcsEepRom(ics::ICS3&, const ics::ID&);
void testIcsID(ics::ICS3&);

template<typename Iter>
constexpr void dump(Iter&& begin, Iter&& end) noexcept;

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
  } catch (const std::out_of_range& e) {
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
  } catch (const std::out_of_range& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    radian.set(M_PI);
    assert(false);
  } catch (const std::out_of_range& e) {
    std::cout << e.what() << std::endl;
  }
}

void testBaudrate() {
  std::cout << std::endl << "Baudrate test section" << std::endl;
  // constexpr test
  constexpr auto baudrate115200 = ics::Baudrate::RATE115200();
  static_assert(baudrate115200 == 10, "Baudrate: not equal B115200");
  static_assert(baudrate115200.get() == 10, "Baudrate: romdata error");
  static_assert(baudrate115200.getSpeed() == B115200, "Baudrate: getSpeed method error");
}

void testEepParam() {
  std::cout << std::endl << "EepParam test section" << std::endl;
  // constexpr test
  constexpr auto current = ics::EepParam::current();
  static_assert(63 == current.get(), "current error");
  constexpr auto stretch = ics::EepParam::stretch(244);
  static_assert(244 == stretch.get(), "strech error");
  try {
    ics::EepParam::flag(10);
    assert(false);
  } catch (const std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
  }

  // runtime test
  auto speed = ics::EepParam::speed();
  assert(127 == speed.get());
  speed.set(100);
  assert(100 == speed.get());
  auto speed2 = ics::EepParam::newEepParam(speed, 60);
  assert(60 == speed2.get());
  try {
    speed.set(200);
    assert(false);
  } catch (const std::out_of_range& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    ics::EepParam::newEepParam(speed2, 130);
    assert(false);
  } catch (const std::out_of_range& e) {
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
  } catch (const std::out_of_range& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    ics::ID error {static_cast<uint8_t>(-1)}; // if constexpr, compile error
    assert(false);
  } catch (const std::out_of_range& e) {
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
  } catch (const std::out_of_range& e) {
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
  } catch (const std::out_of_range& e) {
    std::cout << e.what() << std::endl;
  }
  try {
    current = 64;
    assert(false);
  } catch (const std::out_of_range& e) {
    std::cout << e.what() << std::endl;
  }
}

void testICS3() {
  std::cout << std::endl << "ICS3 test section" << std::endl;
  constexpr const char* const path = "/dev/ttyUSB0";
  constexpr auto baudrate = ics::Baudrate::RATE115200();
  constexpr ics::ID id {2};
  try {
    ics::ICS3 ics {path, baudrate};
    testIcsMove(ics, id);
    testIcsParam(ics, id);
    testIcsEepRom(ics, id);
    testIcsID(ics);
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
}

void testIcsMove(ics::ICS3& ics, const ics::ID& id) {
  std::cout << "ICS3 'move' and 'free' method test section"  << std::endl;
  auto degree = ics::Angle::newDegree();
  std::cout << "move to " << degree << "[deg]" << std::endl;
  auto nowPos = ics.move(id, degree);
  std::cout << "now pos is " << nowPos << "[deg]" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(1500));
  degree = 50;
  std::cout << "move to " << degree << "[deg]" << std::endl;
  nowPos = ics.move(id, degree);
  std::cout << "now pos is " << nowPos << "[deg]" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(1500));
  degree = -50;
  std::cout << "move to " << degree << "[deg]" << std::endl;
  nowPos = ics.move(id, degree);
  std::cout << "now pos is " << nowPos << "[deg]" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(1500));
  degree = 0;
  std::cout << "move to " << degree << "[deg]" << std::endl;
  nowPos = ics.move(id, degree);
  std::cout << "now pos is " << nowPos << "[deg]" << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(1500));
  std::cout << "free torque" << std::endl;
  nowPos = ics.free(id);
  std::cout << "now pos is " << nowPos << "[deg]" << std::endl;
}

void testIcsParam(ics::ICS3& ics, const ics::ID& id) {
  std::cout << "ICS3 'get' and 'set' method test section"  << std::endl;
  auto defaultStretch = ics.get(id, ics::Parameter::stretch());
  std::cout << "default stretch is " << static_cast<int>(defaultStretch) << std::endl;
  constexpr uint8_t writeNumber {29};
  ics.set(id, ics::Parameter::stretch(writeNumber));
  auto newStretch = ics.get(id, defaultStretch);
  ics.set(id, defaultStretch); // before checking, restore data.
  assert(newStretch == writeNumber);
  assert(defaultStretch == ics.get(id, defaultStretch));
}

void testIcsEepRom(ics::ICS3& ics, const ics::ID& id) {
  std::cout << "ics 'getRom' and 'setRom' test section" << std::endl;
  auto rom = ics.getRom(id);
  auto defaultStretch = rom.get(ics::EepParam::stretch());
  std::cout << "default stretch is " << defaultStretch << std::endl;
  auto setRom = rom;
  constexpr uint16_t writeNumber {62};
  setRom.set(ics::EepParam::stretch(writeNumber));
  ics.setRom(id, setRom);
  auto newRom = ics.getRom(id);
  ics.setRom(id, rom); // before checking, restore data.
  assert(newRom.get(defaultStretch) == writeNumber);
  auto lastRom = ics.getRom(id);
  assert(defaultStretch == lastRom.get(defaultStretch));
}

void testIcsID(ics::ICS3& ics) {
  std::cout << "ics 'getID' and 'setID' test section" << std::endl;
  auto defaultID = ics.getID();
  std::cout << "default id is " << static_cast<int>(defaultID.get()) << std::endl;
  constexpr ics::ID newID {20};
  std::this_thread::sleep_for(std::chrono::milliseconds(500)); // need stop time
  ics.setID(newID);
  std::this_thread::sleep_for(std::chrono::milliseconds(500)); // need stop time
  auto checkID = ics.getID();
  std::this_thread::sleep_for(std::chrono::milliseconds(500)); // need stop time
  ics.setID(defaultID); // before checking, restore data.
  std::this_thread::sleep_for(std::chrono::milliseconds(500)); // need stop time
  assert(newID.get() == checkID.get());
  assert(defaultID.get() == ics.getID().get());
}

template<typename Iter>
constexpr void dump(Iter&& begin, Iter&& end) noexcept {
  while (begin != end) std::cout << static_cast<int>(*begin++) << ", ";
  std::cout << std::endl;
}
