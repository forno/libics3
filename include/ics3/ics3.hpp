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

  enum struct ICSBaudrate : speed_t {
    RATE115200 = B115200,
    //RATE625000 = B625000,
    //RATE1250000 = B1250000
  };

  class ICS3 {
  public:
    explicit ICS3(const char*, ICSBaudrate = ICSBaudrate::RATE115200);
    Angle free(const ID&) const;
    Angle free(const ID&, Angle) const;
    Angle move(const ID&, Angle) const;
    Parameter get(const ID&, Parameter) const;
    void set(const ID&, const Parameter&) const;
    Eeprom getRom(const ID&) const;
    void setRom(const ID&, const Eeprom&) const;
  private:
    const Core& core;
  };
}

#endif // LIBICS3_ICS3_ICS3_H_
