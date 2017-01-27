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
#include <cstring> // for memset
#include <sstream> // for error massage
#include <stdexcept>
#include <unordered_map> // for cashe
#include <fcntl.h> // for open FLAGS
#include <unistd.h> // for tty checks

#include "core.hpp"

template<typename T, typename... Args>
inline std::unique_ptr<T> make_unique(Args&&... args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

ics::Core::Core(const std::string& path, speed_t baudrate)
: fd {open(path.c_str(), O_RDWR | O_NOCTTY)},
  oldTio {}
{
  if (fd < 0)
    throw std::runtime_error {"Cannot open deveice"};
  try {
    if (!isatty(fd))
      throw std::invalid_argument {"Not tty device"};
    if (tcgetattr(fd, &oldTio) < 0)
      throw std::runtime_error {"Cannot setup tty"};
    auto newTio = getTermios(); // forward reference
    if (cfsetispeed(&newTio, baudrate) < 0)
      throw std::runtime_error {"Cannot set baudrate"};
    if (cfsetospeed(&newTio, baudrate) < 0)
      throw std::runtime_error {"Cannot set baudrate"};
    if (tcsetattr(fd, TCSANOW, &newTio) < 0)
      throw std::runtime_error {"Cannot setup tty"};
  } catch (...) {
    close(fd);
    throw;
  }
}

ics::Core::~Core() noexcept
{
  if (fd < 0) return;
  closeThis();
}

ics::Core::Core(Core&& rhs) noexcept
: fd {rhs.fd},
  oldTio(rhs.oldTio) // for Ubuntu14.04 compiler
{
  rhs.fd = -1;
}

ics::Core& ics::Core::operator=(Core&& rhs) noexcept
{
  if (fd != rhs.fd) {
    closeThis();
    fd = rhs.fd;
    oldTio = rhs.oldTio;
    rhs.fd = -1;
  }
  return *this;
}

std::unique_ptr<ics::Core> ics::Core::getCore(const std::string& path, speed_t baudrate)
{
  return make_unique<Core>(path, baudrate);
}

void ics::Core::communicate(const Container& tx, Container& rx)
{
  write(fd, tx.data(), tx.size()); // send
  for (auto& receive : rx) read(fd, &receive, 1); // receive
// check section
  auto receive = rx.cbegin();
  for (const auto& send : tx) {
    if (send != *receive) {
      std::stringstream ss;
      ss << "Receive falied(loopback):" << receive - rx.cbegin() << ':' << static_cast<int>(send) << "<->" << static_cast<int>(*receive);
      throw std::runtime_error {ss.str()};
    }
    ++receive;
  }
}

void ics::Core::communicateID(const IDContainerTx& tx, IDContainerRx& rx)
{
  write(fd, tx.data(), tx.size()); // send
  for (auto& receive : rx) read(fd, &receive, 1); // receive
// check section
  auto receive = rx.cbegin();
  for (const auto& send : tx) {
    if (send != *receive) {
      std::stringstream ss;
      ss << "Receive falied(loopback):" << receive - rx.cbegin() << ':' << static_cast<int>(send) << "<->" << static_cast<int>(*receive);
      throw std::runtime_error {ss.str()};
    }
    ++receive;
  }
  if ((tx[0] & 0xE0) != (*receive & 0xE0)) throw std::runtime_error {"Receive failed: invalid target data"};
}

void ics::Core::closeThis() const noexcept
{
  tcsetattr(fd, TCSANOW, &oldTio);
  close(fd);
}

termios ics::Core::getTermios() noexcept
{
  termios newTio;
  std::memset(&newTio, 0, sizeof(newTio));
  newTio.c_iflag = 0;
  newTio.c_oflag = 0;
  newTio.c_cflag = CS8 | CREAD | CLOCAL | PARENB;
  newTio.c_lflag = 0;
  newTio.c_cc[VMIN] = 1;
  newTio.c_cc[VTIME] = 1;
  return newTio;
}
