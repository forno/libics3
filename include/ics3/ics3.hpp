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
#ifndef LIBICS3_ICS3_ICS3_H
#define LIBICS3_ICS3_ICS3_H

#include <memory>
#include <string>

#include "ics3/angle.hpp"
#include "ics3/baudrate.hpp"

namespace ics
{
// Forward declaration
class Core;
class EepRom;
class ID;
class Parameter;

class ICS3
{
public:
  explicit ICS3(const std::string&, const Baudrate& = Baudrate::RATE115200());
  ~ICS3() noexcept;

  Angle move(const ID&, Angle);
  Angle free(const ID&, Angle = Angle::newRadian());
  Parameter get(const ID&, const Parameter&);
  void set(const ID&, const Parameter&);
  EepRom getRom(const ID&);
  void setRom(const ID&, const EepRom&);
  ID getID();
  void setID(const ID&);
private:
  std::unique_ptr<Core> core;
};
}

#endif // LIBICS3_ICS3_ICS3_H
