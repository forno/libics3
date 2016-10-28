#include"core.hpp"

#include<stdexcept>
#include<sstream>
#include<fcntl.h> // for open FLAGS
#include<unistd.h> // for tty checks
#include<cstring> // for memset

ics::Core::~Core() noexcept {
  if (fd < 0) return;
  tcsetattr(fd, TCSANOW, &oldTio);
  close(fd);
}

ics::Core::Core(Core&& rhs)
: fd {rhs.fd},
  oldTio {rhs.oldTio}
{
  rhs.fd = -1;
}

ics::Core& ics::Core::operator=(Core&& rhs) {
  fd = rhs.fd;
  oldTio = rhs.oldTio;
  rhs.fd = -1;
  return *this;
}

ics::Core& ics::Core::getReference(const std::string& path, speed_t baudrate) {
  static Core core {path, baudrate}; // update plan: mutable path and baudrate
  return core;
}

void ics::Core::communicate(std::vector<uint8_t>& tx, std::vector<uint8_t>& rx) {
  write(fd, tx.data(), tx.size()); // send
  for (auto& receive : rx) read(fd, &receive, 1); // receive
// check section
  auto receive = rx.begin();
  for (const auto& send : tx) {
    if (send != *receive) {
      std::stringstream ss;
      ss << "Receive falied:" << receive - rx.begin() << ':' << static_cast<int>(send) << "<->" << static_cast<int>(*receive);
      throw std::runtime_error {ss.str()};
    }
    ++receive;
  }
  if ((tx[0] & 0x7F) != *receive) throw std::runtime_error {"Receive failed: fail make data"};
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
    auto newTio = getTermios();
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

termios ics::Core::getTermios() noexcept {
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
