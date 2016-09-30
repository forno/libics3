#ifndef LIBICS3_ICS3_CORE_H_
#define LIBICS3_ICS3_CORE_H_

#include <vector>
#include <stdexcept>
#include <termios>

namespace ics {
  class Core {
  public:
    static const Core &getReference();
    std::vector<unsigned char> &communicate(std::vector<unsigned char>) const noexcept;
  private:
    explicit Core(const char *) throw(std::runtime_error);
    Core(const Core &);

    int fd;
    termios tio;
  };
}

#endif // LIBICS3_ICS3_CORE_H_
