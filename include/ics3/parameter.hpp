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
#ifndef LIBICS3_ICS3_PARAMETER_H_
#define LIBICS3_ICS3_PARAMETER_H_

#include "ics3/check_invalid.hpp"

namespace ics
{
class Parameter
{
public:
  using type = uint8_t;
  static constexpr Parameter stretch(type = 30);
  static constexpr Parameter speed(type = 127);
  static constexpr Parameter current(type = 63);
  static constexpr Parameter temperature(type = 80);
  static constexpr Parameter newParameter(const Parameter&, type);

  constexpr type get() const noexcept;
  constexpr operator type() const noexcept;
  void set(type);
  Parameter& operator=(type);
  constexpr type getSubcommand() const noexcept;
private:
  constexpr Parameter(type, type, type, type); // non explicit, user cannot touch this

  const type sc;
  const type min;
  const type max;
  type data;
};

constexpr Parameter Parameter::stretch(type data)
{
  return {0x01, 1, 127, data};
}

constexpr Parameter Parameter::speed(type data)
{
  return {0x02, 1, 127, data};
}

constexpr Parameter Parameter::current(type data)
{
  return {0x03, 0, 63, data};
}

constexpr Parameter Parameter::temperature(type data)
{
  return {0x04, 1, 127, data};
}

constexpr Parameter Parameter::newParameter(const Parameter& base, type data)
{
  return {base.sc, base.min, base.max, data};
}

constexpr Parameter::type Parameter::get() const noexcept
{
  return data;
}

constexpr Parameter::operator type() const noexcept
{
  return get();
}

inline void Parameter::set(type input)
{
  data = checkValidRange(input, min, max);
}

inline Parameter& Parameter::operator=(type rhs)
{
  set(rhs);
  return *this;
}

constexpr Parameter::type Parameter::getSubcommand() const noexcept
{
  return sc;
}

constexpr Parameter::Parameter(type sc, type min, type max, type defaultData)
: sc {sc},
  min {min},
  max {max},
  data {checkValidRange(defaultData, min, max)}
{
}
}

#endif // LIBICS3_ICS3_PARAMETER_H_
