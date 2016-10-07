#include "core.hpp"

#include <fcntl.h> // for open FLAGS
#include <unistd.h> // for tty checks
#include <cstring> // for memset

ics::Core::~Core() noexcept {
  if (fd < 0) return;
  tcsetattr(fd, TCSANOW, &oldTio);
  if (fd < 0) return;
  close(fd);
}

const ics::Core& ics::Core::getReference(const char* path, speed_t baudrate = B115200) throw(std::runtime_error) {
  static const Core core(path, baudrate); // update plan: mutable path and baudrate
  return core;
}

void ics::Core::communicate(std::vector<unsigned char>& tx, std::vector<unsigned char>& rx) const throw(std::runtime_error) {
  write(fd, tx.data(), tx.size()); // send
  for (auto receive: rx) read(fd, &receive, 1); // receive
// check section
  auto receive = rx.begin();
  for (auto send: tx) {
    if (send != *receive) throw std::runtime_error("Loopback falied");
    receive++;
  }
  if ((tx[0] & 0x7F) != *receive) throw std::runtime_error("Receive failed");
}

ics::Core::Core(const char* path, speed_t baudrate) throw(std::invalid_argument, std::runtime_error) {
  if ((fd = open(path, O_RDWR | O_NOCTTY | O_NONBLOCK)) < 0)
    throw std::runtime_error("Cannot open deveice");
  if (!isatty(fd))
    throw std::invalid_argument("Not tty device");
  if (tcgetattr(fd, &oldTio) < 0)
    throw std::runtime_error("Cannot setup tty");
  struct termios newTio = getTermios();
  if (cfsetispeed(&newTio, baudrate) < 0)
    throw std::runtime_error("Cannot set baudrate");
  if (cfsetospeed(&newTio, baudrate) < 0)
    throw std::runtime_error("Cannot set baudrate");
  if (tcsetattr(fd, TCSANOW, &newTio) < 0)
    throw std::runtime_error("Cannot setup tty");
}

struct termios ics::Core::getTermios() noexcept {
  struct termios newTio;
  std::memset(&newTio, 0, sizeof(newTio));
  newTio.c_iflag = 0;
  newTio.c_oflag = 0;
  newTio.c_cflag |= CS8 | CREAD | CLOCAL | PARENB;
  newTio.c_lflag = 0;
  newTio.c_cc[VMIN] = 1;
  newTio.c_cc[VTIME] = 0;
  return newTio;
}
