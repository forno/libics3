#ifndef LIBICS3_ICS3_ICS3_H_
#define LIBICS3_ICS3_ICS3_H_

#include<vector>
#include<termios.h>

#include"ics3/angle.hpp"
#include"ics3/baudrate.hpp"

namespace ics {
  // Forward declaration
  class Core;
  class Parameter;
  class Eeprom;
  class ID;

  class ICS3 {
  public:
    explicit ICS3(const char*, const Baudrate& = Baudrate::RATE115200());
    Angle free(const ID&, const Angle& = Angle::newRadian()) const;
    Angle move(const ID&, const Angle&) const;
    Parameter get(const ID&, Parameter) const;
    void set(const ID&, const Parameter&) const;
    Eeprom getRom(const ID&) const;
    void setRom(const ID&, const Eeprom&) const;
  private:
    const Core& core;
  };
}

#endif // LIBICS3_ICS3_ICS3_H_
