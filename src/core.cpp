#include"core.hpp"

#include<stdexcept>
#include<sstream>
#include<fcntl.h> // for open FLAGS
#include<unistd.h> // for tty checks
#include<cstring> // for memset
#include<unordered_map> // for cashe

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

ics::Core::~Core() noexcept {
  if (fd < 0) return;
  tcsetattr(fd, TCSANOW, &oldTio);
  close(fd);
}

ics::Core::Core(Core&& rhs) noexcept
: fd {rhs.fd},
  oldTio(rhs.oldTio) // for Ubuntu14.04 compiler
{
  rhs.fd = -1;
}

ics::Core& ics::Core::operator=(Core&& rhs) noexcept {
  fd = rhs.fd;
  oldTio = rhs.oldTio;
  rhs.fd = -1;
  return *this;
}

std::shared_ptr<ics::Core> ics::Core::getCore(const std::string& path, speed_t baudrate) {
  static std::unordered_map<std::string, std::weak_ptr<Core>> cache;
  auto objPtr = cache[path].lock(); // try get
  for (const auto& data : cache) if (data.second.expired()) cache.erase(data.first); // clean cashe
  if (!objPtr) { // get failed
    objPtr = std::make_shared<Core>(path, baudrate);
    cache[path] = objPtr;
  }
  return objPtr;
}

void ics::Core::communicate(const Container& tx, Container& rx) {
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
  if ((tx[0] & 0x7F) != *receive) throw std::runtime_error {"Receive failed: invalid target data"};
}

void ics::Core::communicateID(const IDContainerTx& tx, IDContainerRx& rx) {
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
