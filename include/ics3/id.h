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
#ifndef LIBICS3_ICS3_ID_H
#define LIBICS3_ICS3_ID_H

#include <stdexcept>

namespace ics
{
class ID
{
public:
  using type = uint8_t;
  constexpr ID(type); // ID is non explicit constructor because only do check limit
  constexpr type get() const noexcept;
  constexpr operator type() const noexcept;
private:
  const type data;
};

constexpr ID::ID(type id)
: data {id < 32 ? id : throw std::invalid_argument {"invalid ID: must be 0 <= id <= 31"}}
{
}

constexpr ID::type ID::get() const noexcept
{
  return data;
}

constexpr ID::operator type() const noexcept
{
  return get();
}
}

#endif // LIBICS3_ICS3_ID_H
