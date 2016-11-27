/* BSD 2-Clause License

Copyright (c) 2016, Doi Yusuke
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "ics3/ics"

#include <chrono>
#include <iostream>
#include <thread>

#include <gtest/gtest.h>

void testIcsMove(ics::ICS3&, const ics::ID&);
void testIcsParam(ics::ICS3&, const ics::ID&);
void testIcsEepRom(ics::ICS3&, const ics::ID&);
void testIcsID(ics::ICS3&);

template<typename Iter>
void dump(const Iter& begin, const Iter& end) noexcept;

TEST(AllTestInIntegrate, Angle) {
  // constexpr test
  constexpr auto defDeg = ics::Angle::newDegree();
  constexpr auto defRad = ics::Angle::newRadian();
  static_assert(defDeg == 0, "Angle default cast error");
  static_assert(defRad.get() == 0, "Angle default get() error");
  static_assert(defDeg.getRaw() == 7500, "Angle default must is 7500");
  static_assert(defDeg.getRaw() == defRad.getRaw(), "Angle have different default");
  constexpr auto degree1 = ics::Angle::newDegree(90);
  constexpr auto radian1 = ics::Angle::newRadian(ics::Angle::PI / 2);
  static_assert(degree1.getRaw() == radian1.getRaw(), "difference: 90 deg <-> pi/2 rad");
  constexpr auto degree2 = ics::Angle::newDegree(30);
  constexpr auto radian2 = ics::Angle::newRadian(ics::Angle::PI / 6);
  static_assert(degree2.getRaw() == radian2.getRaw(), "difference: 30 deg <-> pi/6 rad");
  constexpr auto degree_cast = ics::Angle::newDegree(50);
  constexpr auto cast1 = static_cast<double>(degree_cast);
  constexpr double cast2 {degree_cast};
  static_assert(cast1 == cast2, "difference: angle cast to doubles. miss? impossible lol");
  EXPECT_THROW(ics::Angle::newDegree(136), std::out_of_range);

  // runtime test
  auto degree = ics::Angle::newDegree(0);
  auto radian = ics::Angle::newRadian(0);
  EXPECT_EQ(degree.getRaw(), radian.getRaw());
  degree.set(90);
  radian.set(ics::Angle::PI / 2);
  EXPECT_EQ(degree.getRaw(), radian.getRaw());
  degree.set(-60);
  radian.set(-ics::Angle::PI / 3);
  EXPECT_EQ(degree.getRaw(), radian.getRaw());
  EXPECT_THROW(degree.set(150), std::out_of_range);
  EXPECT_THROW(radian.set(ics::Angle::PI), std::out_of_range);
}

TEST(AllTestInIntegrate, Baudrate) {
  // constexpr test
  constexpr auto baudrate115200 = ics::Baudrate::RATE115200();
  static_assert(baudrate115200 == 10, "Baudrate: not equal 10");
  static_assert(baudrate115200.get() == 10, "Baudrate: romdata error");
  static_assert(baudrate115200.getSpeed() == B115200, "Baudrate: getSpeed method error");
  static_assert(static_cast<uint8_t>(baudrate115200) == 10, "cast to Baudrate::type(uint8_t)");
}

TEST(AllTestInIntegrate, EepParam) {
  // constexpr test
  constexpr auto current = ics::EepParam::current();
  static_assert(63 == current.get(), "current error");
  constexpr auto stretch = ics::EepParam::stretch(244);
  static_assert(244 == stretch.get(), "strech error");
  EXPECT_THROW(ics::EepParam::flag(10), std::invalid_argument);

  // runtime test
  auto speed = ics::EepParam::speed();
  EXPECT_EQ(127, speed.get());
  speed.set(100);
  EXPECT_EQ(100, speed.get());
  auto speed2 = ics::EepParam::newEepParam(speed, 60);
  EXPECT_EQ(60, speed2.get());
  EXPECT_THROW(speed.set(200), std::out_of_range);
  EXPECT_THROW(ics::EepParam::newEepParam(speed2, 130), std::out_of_range);
}

TEST(AllTestInIntegrate, ID) {
  constexpr ics::ID id {0};
  static_assert(id == 0, "id 0 error");
  static_assert(id.get() == 0, "id 0 error by get");
  constexpr ics::ID id31 {31};
  static_assert(id31 == 31, "id 31 error");
  static_assert(id31.get() == 31, "id 31 error by get");
  EXPECT_THROW(ics::ID {32}, std::invalid_argument);
  EXPECT_THROW(ics::ID {static_cast<ics::ID::type>(-1)}, std::invalid_argument);
}

TEST(AllTestInIntegrate, Parameter) {
  // constexpr test
  constexpr auto stretch = ics::Parameter::stretch();
  static_assert(30 == stretch.get(), "stretch error");
  static_assert(30 == stretch, "stretch error by cast");
  static_assert(0x01 == stretch.getSubcommand(), "stretch error by subcommand");
  constexpr auto speed = ics::Parameter::speed(100);
  static_assert(100 == speed.get(), "speed error");
  static_assert(100 == speed, "speed error by cast");
  static_assert(0x02 == speed.getSubcommand(), "speed error by subcommand");
  EXPECT_THROW(ics::Parameter::temperature(0), std::out_of_range);

  // runtime test
  auto current = ics::Parameter::current();
  EXPECT_EQ(63, current.get());
  EXPECT_EQ(0x03, current.getSubcommand());
  current.set(30);
  EXPECT_EQ(30, current);
  current = 10;
  EXPECT_EQ(10, current);
  EXPECT_THROW(current.set(70), std::out_of_range);
  EXPECT_THROW(current = 64;, std::out_of_range);
}

TEST(AllTestInIntegrate, ICS3) {
  constexpr auto path = "/dev/ttyUSB0";
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
  constexpr ics::Parameter::type writeNumber {29};
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
  constexpr ics::EepParam::type writeNumber {62};
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
inline void dump(const Iter& begin, const Iter& end) noexcept {
  while (begin != end) std::cout << static_cast<int>(*begin++) << ", ";
  std::cout << std::endl;
}
