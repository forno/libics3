#ifndef LIBICS3_ICS3_ICS3_H_
#define LIBICS3_ICS3_ICS3_H_

#include <stdexcept>
#include <vector>
#include <termios.h>

namespace ics {
  // Forward declaration
  class Core;
  class Angle;
  class Parameter;
  class Eeprom;
  class ID;

  class ICS3 {
  public:
    enum Baudrate : speed_t {
      RATE115200 = B115200,
      //RATE625000 = B625000,
      //RATE1250000 = B1250000
    };

    ICS3(const char *, Baudrate) throw(std::invalid_argument, std::runtime_error);
    Angle move(const ID &, Angle) const throw(std::runtime_error);
    Parameter get(const ID &, Parameter) const throw(std::runtime_error);
    void set(const ID &, const Parameter &) const throw(std::runtime_error);
    Eeprom getRom(const ID &) const throw(std::runtime_error);
    void setRom(const ID &, const Eeprom &) const throw(std::runtime_error);
  private:
    const Core &core;
  };
}

#endif // LIBICS3_ICS3_ICS3_H_
