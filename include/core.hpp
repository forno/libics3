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
#ifndef LIBICS3_ICS3_CORE_H
#define LIBICS3_ICS3_CORE_H

#include <array>
#include <memory>
#include <string>
#include <vector>

#include <termios.h>

namespace ics
{
class Core
{
public:
  using value_type = uint8_t;
  using Container = std::vector<value_type>;
  using IDContainerTx = std::array<value_type, 4>;
  using IDContainerRx = std::array<value_type, 5>;
  explicit Core(const std::string&, speed_t); // touch by only libics3
  ~Core() noexcept;
  Core(const Core&) = delete;
  Core& operator=(const Core&) = delete;
  Core(Core&&) noexcept;
  Core& operator=(Core&&) noexcept;

  static std::unique_ptr<Core> getCore(const std::string&, speed_t);
  void communicate(const Container&, Container&);
  void communicateID(const IDContainerTx&, IDContainerRx&);
private:
  void closeThis() const noexcept;

  static termios getTermios() noexcept;

  int fd;
  termios oldTio;
};
}

#endif // LIBICS3_ICS3_CORE_H
