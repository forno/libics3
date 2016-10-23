#ifndef LIBICS3_ICS3_ICS3_H_
#define LIBICS3_ICS3_ICS3_H_

#include<string>
#include<termios.h>

#include"ics3/angle.hpp"
#include"ics3/baudrate.hpp"

namespace ics {
  // Forward declaration
  class Core;
  class Parameter;
  class EepRom;
  class ID;

  class ICS3 {
  public:
    explicit ICS3(const std::string&, const Baudrate& = Baudrate::RATE115200());
    Angle free(const ID&, Angle = Angle::newRadian()) const;
    Angle move(const ID&, Angle) const;
    Parameter get(const ID&, const Parameter&) const;
    void set(const ID&, const Parameter&) const;
    EepRom getRom(const ID&) const;
    void setRom(const ID&, const EepRom&) const;
  private:
    const Core& core;
  };
}

#endif // LIBICS3_ICS3_ICS3_H_
