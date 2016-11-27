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
#ifndef LIBICS3_ICS3_BAUDRATE_H_
#define LIBICS3_ICS3_BAUDRATE_H_

#include <termios.h>

namespace ics
{
class Baudrate
{
public:
  using type = uint8_t;
  static constexpr Baudrate RATE115200() noexcept;
  //static constexpr Baudrate RATE625000() noexcept;
  //static constexpr Baudrate RATE1250000() noexcept;
  constexpr type get() const noexcept;
  constexpr operator type() const noexcept;
  constexpr speed_t getSpeed() const noexcept;
private:
  constexpr Baudrate(type, speed_t) noexcept; // non explicit, user cannot touch this

  const type romdata;
  const speed_t baudrate;
};

constexpr Baudrate Baudrate::RATE115200() noexcept
{
  return {10, B115200};
}

constexpr Baudrate::type Baudrate::get() const noexcept
{
  return romdata;
}

constexpr Baudrate::operator Baudrate::type() const noexcept
{
  return get();
}

constexpr speed_t Baudrate::getSpeed() const noexcept
{
  return baudrate;
}

constexpr Baudrate::Baudrate(type romdata, speed_t baudrate) noexcept
: romdata {romdata},
  baudrate {baudrate}
{
}
}

#endif // LIBICS3_ICS3_BAUDRATE_H_
