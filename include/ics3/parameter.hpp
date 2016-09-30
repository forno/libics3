#ifndef LIBICS3_ICS3_PARAMETER_H_
#define LIBICS3_ICS3_PARAMETER_H_

#include <stdexcept>

namespace ics {
  class ICS3;

  class Parameter {
  public:
    friend ICS3;
    static Parameter stretch() noexcept;
    static Parameter speed() noexcept;
    static Parameter current() noexcept;
    static Parameter temperature() noexcept;

    unsigned char get() const noexcept;
    void set(unsigned char) throw(std::invalid_argument);
  private:
    Parameter(unsigned char, unsigned char, unsigned char, unsigned char) noexcept;
    const unsigned char sc;
    const unsigned char min;
    const unsigned char max;
    unsigned char data;
  };
}

#endif // LIBICS3_ICS3_PARAMETER_H_
