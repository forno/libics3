#ifndef LIBICS3_ICS3_CORE_H_
#define LIBICS3_ICS3_CORE_H_

#include <vector>
#include <stdexcept>
#include <termios.h>

namespace ics {
  class Core {
  public:
    ~Core() noexcept;
    static const Core& getReference(const char*, speed_t); 
    void communicate(std::vector<unsigned char>&, std::vector<unsigned char>&) const;
  private:
    Core(const char*, speed_t);
    Core(const Core&) = delete;
    static struct termios getTermios() noexcept;

    int fd;
    termios oldTio;
  };
}

#endif // LIBICS3_ICS3_CORE_H_
