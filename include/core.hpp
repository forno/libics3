#ifndef LIBICS3_ICS3_CORE_H_
#define LIBICS3_ICS3_CORE_H_

#include <vector>
#include <stdexcept>
#include <termios.h>

namespace ics {
  class Core {
  public:
    ~Core() noexcept;
    static const Core& getReference(const char*, speed_t) throw(std::invalid_argument, std::runtime_error); 
    void communicate(std::vector<unsigned char>&, std::vector<unsigned char>&) const throw(std::runtime_error);
  private:
    Core(const char*, speed_t) throw(std::invalid_argument, std::runtime_error);
    Core(const Core&); // not implement this copy constructor
    static struct termios getTermios() noexcept;

    int fd;
    termios oldTio;
  };
}

#endif // LIBICS3_ICS3_CORE_H_
