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

TEST(ParameterConstexprTest, Parameter) {
  constexpr auto stretch = ics::Parameter::stretch();
  static_assert(30 == stretch.get(), "stretch error");
  static_assert(30 == stretch, "stretch error by cast");
  static_assert(0x01 == stretch.getSubcommand(), "stretch error by subcommand");
  constexpr auto speed = ics::Parameter::speed(100);
  static_assert(100 == speed.get(), "speed error");
  static_assert(100 == speed, "speed error by cast");
  static_assert(0x02 == speed.getSubcommand(), "speed error by subcommand");
}

TEST(EepParamCreateTest, Correct) {
  ics::Parameter::current();
}

TEST(EepParamCreateTest, Invalid) {
  EXPECT_THROW(ics::Parameter::temperature(0), std::out_of_range);
}

TEST(EepParamMethodSetTest, Correct) {
  auto current = ics::Parameter::current();
  EXPECT_EQ(63, current.get());
  EXPECT_EQ(0x03, current.getSubcommand());
  current.set(30);
  EXPECT_EQ(30, current);
  current = 10;
  EXPECT_EQ(10, current);
}

TEST(EepParamMethodSetTest, Invalid) {
  auto current = ics::Parameter::current();
  EXPECT_THROW(current.set(70), std::out_of_range);
  EXPECT_THROW(current = 64;, std::out_of_range);
}
