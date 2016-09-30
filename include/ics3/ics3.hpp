#ifndef LIBICS3_ICS3_ICS3_H_
#define LIBICS3_ICS3_ICS3_H_

#include <stdexcept>

namespace ics {
  // Forward declaration
  class Core;
  class Angle;
  class Parameter;
  class Eeprom;

  class ICS3 {
  public:
    ICS3() throw(std::runtime_error);
    Angle move(Angle) const noexcept;
    Parameter get(const Parameter &) const noexcept;
    void set(const Parameter &) const noexcept;
    Eeprom getRom() const noexcept;
    void setRom(const Eeprom &) const noexcept;

  private:
    const Core &core;
  };
}

#endif // LIBICS3_ICS3_ICS3_H_
