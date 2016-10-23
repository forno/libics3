#ifndef LIBICS3_ICS3_CORE_H_
#define LIBICS3_ICS3_CORE_H_

#include<vector>
#include<termios.h>
#include<string>

namespace ics {
  class Core {
  public:
    ~Core() noexcept;
    static const Core& getReference(const std::string&, speed_t); 
    void communicate(std::vector<uint8_t>&, std::vector<uint8_t>&) const;
  private:
    explicit Core(const std::string&, speed_t);
    static termios getTermios() noexcept;

    int fd;
    termios oldTio;
  };
}

#endif // LIBICS3_ICS3_CORE_H_
