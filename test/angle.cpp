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

#include <gtest/gtest.h>

TEST(AngleConstexprTest, CreateWithGetRaw) {
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
}

TEST(AngleCreateTest, NewFactoryWithGetAndGetRaw) {
  // runtime test
  auto degree = ics::Angle::newDegree();
  auto radian = ics::Angle::newRadian();
  EXPECT_EQ(degree.get(), radian.get());
  EXPECT_EQ(degree.getRaw(), radian.getRaw());
  EXPECT_THROW(ics::Angle::newDegree(136), std::out_of_range);
}

TEST(AngleMethodTest, SetWithGetRaw) {
  auto degree = ics::Angle::newDegree(0);
  auto radian = ics::Angle::newRadian(0);
  degree.set(90);
  radian.set(ics::Angle::PI / 2);
  EXPECT_EQ(degree.getRaw(), radian.getRaw());
  degree.set(-60);
  radian.set(-ics::Angle::PI / 3);
  EXPECT_EQ(degree.getRaw(), radian.getRaw());
  EXPECT_THROW(degree.set(150), std::out_of_range);
  EXPECT_THROW(radian.set(ics::Angle::PI), std::out_of_range);
}
