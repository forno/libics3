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

TEST(EepParamConstexprTest, EepParam) {
  constexpr auto current = ics::EepParam::current();
  static_assert(63 == current.get(), "current error");
  constexpr auto stretch = ics::EepParam::stretch(244);
  static_assert(244 == stretch.get(), "strech error");
}

TEST(EepParamCreateTest, Correct) {
  auto speed = ics::EepParam::speed();
  EXPECT_EQ(speed.get(), 127);
  auto speed2 = ics::EepParam::newEepParam(speed, 60);
  EXPECT_EQ(speed2.get(), 60);
}

TEST(EepParamCreateTest, Invalid) {
  EXPECT_THROW(ics::EepParam::flag(10), std::invalid_argument);
  auto speed = ics::EepParam::speed();
  EXPECT_THROW(ics::EepParam::newEepParam(speed, 130), std::out_of_range);
}

TEST(EepParamMethodSetTest, Correct) {
  // runtime test
  auto speed = ics::EepParam::speed();
  speed.set(100);
  EXPECT_EQ(100, speed.get());
}

TEST(EepParamMethodSetTest, Invalid) {
  auto speed = ics::EepParam::speed();
  EXPECT_THROW(speed.set(200), std::out_of_range);
}
